#include "../../../inc/slib/core/definition.h"

#if defined(SLIB_PLATFORM_IS_OSX)

#include "../../../inc/slib/ui/list_details_view.h"

#include "ui_view_osx.h"

@interface _Slib_OSX_ListDetailsView_TableView : NSTableView {
	
	@public slib::WeakRef<slib::OSX_ViewInstance> m_viewInstance;
}
@end

@interface _Slib_OSX_ListDetailsView : NSScrollView<NSTableViewDataSource, NSTableViewDelegate> {

	@public _Slib_OSX_ListDetailsView_TableView* table;

	@public slib::WeakRef<slib::OSX_ViewInstance> m_viewInstance;
		
	@public slib::List<NSTableColumn*> m_columns;
	
	@public NSFont* m_font;
}
@end

SLIB_UI_NAMESPACE_BEGIN
class _ListDetailsView : public ListDetailsView
{
public:
	void __applyColumnsCount(_Slib_OSX_ListDetailsView* tv)
	{
		MutexLocker lock(getLocker());
		List<NSTableColumn*> _columns = tv->m_columns;
		sl_uint32 nOrig = (sl_uint32)(_columns.count());
		sl_uint32 nNew = (sl_uint32)(m_columns.count());
		if (nOrig == nNew) {
			return;
		}
		if (nOrig > nNew) {
			ListLocker<NSTableColumn*> columns(_columns);
			for (sl_uint32 i = nNew; i < columns.count(); i++) {
				[tv->table removeTableColumn:(columns[i])];
			}
			_columns.setCount(nNew);
		} else {
			_columns.setCount(nNew);
			ListLocker<NSTableColumn*> columns(_columns);
			for (sl_uint32 i = nOrig; i < columns.count(); i++) {
				NSTableColumn* column = [[NSTableColumn alloc] initWithIdentifier:[NSString stringWithFormat:@"%d",i]];
				[tv->table addTableColumn:column];
				columns[i] = column;
			}
		}
	}
	
	void __copyColumns(_Slib_OSX_ListDetailsView* tv)
	{
		ListLocker<ListDetailsViewColumn> columns(m_columns);
		__applyColumnsCount(tv);
		for (sl_uint32 i = 0; i < columns.count(); i++) {
			NSTableColumn* tc = tv->m_columns.getItemValue(i, nil);
			if (tc != nil) {
				[tc setTitle:(Apple::getNSStringFromString(columns[i].title))];
				[tc setWidth:columns[i].width];
				NSTableHeaderCell* headerCell = [tc headerCell];
				NSCell* dataCell = [tc dataCell];
				[headerCell setAlignment:translateAlignment(columns[i].headerAlign)];
				[dataCell setAlignment:translateAlignment(columns[i].align)];
				[dataCell setEditable:FALSE];
			}
		}
	}
	
	void __applyFont(_Slib_OSX_ListDetailsView* tv)
	{
		NSFont* font = tv->m_font;
		if (font != nil) {
			ListLocker<ListDetailsViewColumn> columns(m_columns);
			for (sl_uint32 i = 0; i < columns.count(); i++) {
				NSTableColumn* tc = tv->m_columns.getItemValue(i, nil);
				if (tc != nil) {
					NSCell* dataCell = [tc dataCell];
					[dataCell setFont:font];
				}
			}
		}
		[tv->table setRowHeight:([font pointSize] - [font descender])];
	}
	
	static NSTextAlignment translateAlignment(Alignment _align)
	{
		sl_uint32 align = _align & alignHorizontalMask;
		if (align == alignCenter) {
			return NSCenterTextAlignment;
		} else if (align == alignRight) {
			return NSRightTextAlignment;
		}
		return NSLeftTextAlignment;
	}
	
};

Ref<ViewInstance> ListDetailsView::createInstance(ViewInstance* _parent)
{
	_Slib_OSX_ListDetailsView_TableView* table = nil;
	MutexLocker lock(getLocker());
	OSX_VIEW_CREATE_INSTANCE_BEGIN
	_Slib_OSX_ListDetailsView* handle = nil;
	table = [[_Slib_OSX_ListDetailsView_TableView alloc] init];
	if (table != nil) {
		handle = [[_Slib_OSX_ListDetailsView alloc] initWithFrame:frame];
		if (handle != nil) {
			handle->table = table;
			[table setDelegate:handle];
			[table setDataSource:handle];
			
			Ref<Font> font = m_font;
			Ref<FontInstance> fontInstance;
			NSFont* hFont = UIPlatform::getNSFont(font.get(), fontInstance);
			handle->m_font = hFont;
			((_ListDetailsView*)this)->__copyColumns(handle);
			[table setRowSizeStyle:NSTableViewRowSizeStyleCustom];
			((_ListDetailsView*)this)->__applyFont(handle);
			
			[handle setDocumentView:table];
			[handle setHasVerticalScroller:TRUE];
			[handle setHasHorizontalScroller:TRUE];
			[handle setBorderType:NSBezelBorder];
			[table setGridStyleMask:NSTableViewSolidVerticalGridLineMask | NSTableViewSolidHorizontalGridLineMask];
		}
	}
	OSX_VIEW_CREATE_INSTANCE_END
	if (ret.isNotNull()) {
		ret->setView(this);
		[table reloadData];
	}
	table->m_viewInstance = ret;
	return Ref<ViewInstance>::from(ret);
}

void ListDetailsView::_refreshColumnsCount()
{
	NSView* handle = UIPlatform::getViewHandle(this);
	if (handle != nil && [handle isKindOfClass:[_Slib_OSX_ListDetailsView class]]) {
		_Slib_OSX_ListDetailsView* tv = (_Slib_OSX_ListDetailsView*)handle;
		((_ListDetailsView*)this)->__applyColumnsCount(tv);
		[tv->table reloadData];
	}
}

void ListDetailsView::_refreshRowsCount()
{
	NSView* handle = UIPlatform::getViewHandle(this);
	if (handle != nil && [handle isKindOfClass:[_Slib_OSX_ListDetailsView class]]) {
		_Slib_OSX_ListDetailsView* tv = (_Slib_OSX_ListDetailsView*)handle;
		[tv->table reloadData];
	}
}

void ListDetailsView::_setHeaderText(sl_uint32 iCol, const String& text)
{
	NSView* handle = UIPlatform::getViewHandle(this);
	if (handle != nil && [handle isKindOfClass:[_Slib_OSX_ListDetailsView class]]) {
		_Slib_OSX_ListDetailsView* tv = (_Slib_OSX_ListDetailsView*)handle;
		NSTableColumn* tc = tv->m_columns.getItemValue(iCol, nil);
		if (tc != nil) {
			[tc setTitle:Apple::getNSStringFromString(text)];
		}
	}
}

void ListDetailsView::_setColumnWidth(sl_uint32 iCol, sl_real width)
{
	NSView* handle = UIPlatform::getViewHandle(this);
	if (handle != nil && [handle isKindOfClass:[_Slib_OSX_ListDetailsView class]]) {
		_Slib_OSX_ListDetailsView* tv = (_Slib_OSX_ListDetailsView*)handle;
		NSTableColumn* tc = tv->m_columns.getItemValue(iCol, nil);
		if (tc != nil) {
			[tc setWidth:width];
		}
	}
}

void ListDetailsView::_setHeaderAlignment(sl_uint32 iCol, Alignment align)
{
	NSView* handle = UIPlatform::getViewHandle(this);
	if (handle != nil && [handle isKindOfClass:[_Slib_OSX_ListDetailsView class]]) {
		_Slib_OSX_ListDetailsView* tv = (_Slib_OSX_ListDetailsView*)handle;
		NSTableColumn* tc = tv->m_columns.getItemValue(iCol, nil);
		if (tc != nil) {
			[[tc headerCell] setAlignment:_ListDetailsView::translateAlignment(align)];
		}
	}
}

void ListDetailsView::_setColumnAlignment(sl_uint32 iCol, Alignment align)
{
	NSView* handle = UIPlatform::getViewHandle(this);
	if (handle != nil && [handle isKindOfClass:[_Slib_OSX_ListDetailsView class]]) {
		_Slib_OSX_ListDetailsView* tv = (_Slib_OSX_ListDetailsView*)handle;
		NSTableColumn* tc = tv->m_columns.getItemValue(iCol, nil);
		if (tc != nil) {
			[[tc dataCell] setAlignment:_ListDetailsView::translateAlignment(align)];
		}
	}
}

sl_int32 ListDetailsView::getSelectedRow()
{
	NSView* handle = UIPlatform::getViewHandle(this);
	if (handle != nil && [handle isKindOfClass:[_Slib_OSX_ListDetailsView class]]) {
		_Slib_OSX_ListDetailsView* tv = (_Slib_OSX_ListDetailsView*)handle;
		return (sl_int32)([tv->table selectedRow]);
	}
	return -1;
}

void ListDetailsView::setFont(const Ref<Font>& _font)
{
	Ref<Font> font = _font;
	NSView* handle = UIPlatform::getViewHandle(this);
	if (handle != nil && [handle isKindOfClass:[_Slib_OSX_ListDetailsView class]]) {
		_Slib_OSX_ListDetailsView* tv = (_Slib_OSX_ListDetailsView*)handle;
		Ref<FontInstance> fontInstance;
		NSFont* hFont = UIPlatform::getNSFont(font.get(), fontInstance);
		tv->m_font = hFont;
		((_ListDetailsView*)this)->__applyFont(tv);
		[tv->table reloadData];
	}
	m_font = font;
}
SLIB_UI_NAMESPACE_END

@implementation _Slib_OSX_ListDetailsView
-(id)initWithFrame:(NSRect)frame
{
	self = [super initWithFrame:frame];
	if (self != nil) {
		self->m_columns.setCount(0);
	}
	return self;
}

- (NSInteger)numberOfRowsInTableView:(NSTableView *)tableView{
	slib::Ref<slib::OSX_ViewInstance> instance = m_viewInstance.lock();
	if (instance.isNotNull()) {
		slib::Ref<slib::View> view = instance->getView();
		if (slib::ListDetailsView::checkInstance(view)) {
			return ((slib::_ListDetailsView*)(view.get()))->getRowsCount();
		}
	}
	return 0;
}

- (id)tableView:(NSTableView *)tableView objectValueForTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row{
	slib::Ref<slib::OSX_ViewInstance> instance = m_viewInstance.lock();
	if (instance.isNotNull()) {
		slib::Ref<slib::View> view = instance->getView();
		if (slib::ListDetailsView::checkInstance(view)) {
			NSString* _id = tableColumn.identifier;
			if (_id != nil) {
				sl_uint32 iRow = (sl_uint32)(row);
				sl_uint32 iCol = (sl_uint32)(_id.intValue);
				return slib::Apple::getNSStringFromString(((slib::_ListDetailsView*)(view.get()))->onGetCellText(iRow, iCol));
			}
		}
	}
	return @"";
}

- (void)tableViewSelectionDidChange:(NSNotification *)aNotification
{
	slib::Ref<slib::OSX_ViewInstance> instance = m_viewInstance.lock();
	if (instance.isNotNull()) {
		slib::Ref<slib::View> view = instance->getView();
		if (slib::ListDetailsView::checkInstance(view)) {
			sl_int32 n = (sl_int32)([table selectedRow]);
			if (n >= 0) {
				((slib::_ListDetailsView*)(view.get()))->onSelectRow(n);
			}
		}
	}
}
@end

@implementation _Slib_OSX_ListDetailsView_TableView
- (void)mouseDown:(NSEvent *)theEvent
{
	NSInteger indexRowBefore = [self selectedRow];
	[super mouseDown:theEvent];
	NSPoint ptWindow = [theEvent locationInWindow];
	NSPoint ptView = [self convertPoint:ptWindow fromView:nil];
	NSInteger indexRow = [self rowAtPoint:ptView];
	if (indexRow >= 0) {
		slib::Ref<slib::OSX_ViewInstance> instance = m_viewInstance.lock();
		if (instance.isNotNull()) {
			slib::Ref<slib::View> view = instance->getView();
			if (slib::ListDetailsView::checkInstance(view)) {
				if (indexRow == indexRowBefore) {
					// don't call event callback when it is new selection because it is already called by default
					((slib::_ListDetailsView*)(view.get()))->onSelectRow((sl_uint32)(indexRow));
				}
				sl_real x = (sl_real)(ptView.x);
				sl_real y = (sl_real)(ptView.y);
				NSInteger clicks = [theEvent clickCount];
				if (clicks == 1) {
					((slib::_ListDetailsView*)(view.get()))->onClickRow((sl_uint32)(indexRow), slib::Point(x, y));
				} else if (clicks == 2) {
					((slib::_ListDetailsView*)(view.get()))->onDoubleClickRow((sl_uint32)(indexRow), slib::Point(x, y));
				}
			}
		}
	}
}

- (void)rightMouseDown:(NSEvent *)theEvent
{
	[super rightMouseDown:theEvent];
	NSPoint ptWindow = [theEvent locationInWindow];
	NSPoint ptView = [self convertPoint:ptWindow fromView:nil];
	NSInteger indexRow = [self rowAtPoint:ptView];
	if (indexRow >= 0) {
		slib::Ref<slib::OSX_ViewInstance> instance = m_viewInstance.lock();
		if (instance.isNotNull()) {
			slib::Ref<slib::View> view = instance->getView();
			if (slib::ListDetailsView::checkInstance(view)) {
				sl_real x = (sl_real)(ptView.x);
				sl_real y = (sl_real)(ptView.y);
				((slib::_ListDetailsView*)(view.get()))->onRightButtonClickRow((sl_uint32)(indexRow), slib::Point(x, y));
			}
		}
	}
}
@end

#endif
