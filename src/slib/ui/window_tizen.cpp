#include "../../../inc/slib/core/definition.h"

#if defined(SLIB_PLATFORM_IS_TIZEN)

#include "../../../inc/slib/ui/window.h"
#include "../../../inc/slib/ui/view.h"
#include "../../../inc/slib/ui/screen.h"
#include "../../../inc/slib/ui/core.h"
#include "../../../inc/slib/ui/mobile_app.h"
#include "../../../inc/slib/ui/platform.h"

#include "view_tizen.h"

#pragma GCC diagnostic ignored "-Wextern-c-compat"

#include <app.h>
#include <Elementary.h>
#include <efl_extension.h>

namespace slib
{

	static sl_int32 _ui_active_windows_count = 0;

	class _Tizen_Window : public WindowInstance
	{
	public:
		Evas_Object* m_window;
		AtomicRef<ViewInstance> m_viewContent;
		
	public:
		_Tizen_Window()
		{
			m_window = sl_null;
		}
		
		~_Tizen_Window()
		{
			_release();
		}
		
	public:
		static Ref<_Tizen_Window> create(Evas_Object* window)
		{
			if (window) {
				Ref<_Tizen_Window> ret = new _Tizen_Window();
				if (ret.isNotNull()) {
					ret->m_window = window;
					Ref<ViewInstance> content = UIPlatform::createViewInstance(window, sl_false);
					if (content.isNotNull()) {
						content->setWindowContent(sl_true);
						ret->m_viewContent = content;
					}

					Base::interlockedIncrement32(&_ui_active_windows_count);
					::evas_object_smart_callback_add(window, "delete,request", _ui_win_delete_request_cb, window);
					::eext_object_event_callback_add(window, EEXT_CALLBACK_BACK, _ui_win_back_cb, window);

					::evas_object_show(window);

					return ret;
				}
			}
			return sl_null;
		}
		
		static void _ui_win_delete_request_cb(void* data, Evas_Object* obj, void* event_info)
		{
			Evas_Object* win = reinterpret_cast<Evas_Object*>(data);
			Ref<WindowInstance> instance = UIPlatform::getWindowInstance(win);
			if (instance.isNotNull()) {
				(static_cast<_Tizen_Window*>(instance.get()))->m_window = sl_null;
			}
			UIPlatform::removeWindowInstance(win);
			sl_int32 n = Base::interlockedDecrement32(&_ui_active_windows_count);
			if (n <= 0) {
				::ui_app_exit();
			}
		}

		static void _ui_win_back_cb(void* data, Evas_Object* obj, void* event_info)
		{
			Evas_Object* win = reinterpret_cast<Evas_Object*>(data);
			if (MobileApp::dispatchBackToApp()) {
				::elm_win_lower(win);
			}
		}

		static Ref<WindowInstance> create(const WindowInstanceParam& param)
		{
			Evas_Object* win = ::elm_win_add(NULL, "", ELM_WIN_BASIC);
			if (win) {

				if (!(param.flagFullScreen)) {
					UIRect screenFrame;
					Ref<Screen> _screen = param.screen;
					if (_screen.isNotNull()) {
						screenFrame = _screen->getRegion();
					} else {
						_screen = UI::getPrimaryScreen();
						if (_screen.isNotNull()) {
							screenFrame = _screen->getRegion();
						} else {
							screenFrame = UIRect::zero();
						}
					}
					UIRect rect = param.calculateRegion(screenFrame);
					/*
					 * Following move&resize code has no effect because Tizen policy fills the window in the screen.
					 * Just left for the further update.
					 */
					::evas_object_move(win, (Evas_Coord)(rect.left), (Evas_Coord)(rect.top));
					::evas_object_resize(win, (Evas_Coord)(rect.getWidth()), (Evas_Coord)(rect.getHeight()));
				}

				Ref<_Tizen_Window> ret = Ref<_Tizen_Window>::from(UIPlatform::createWindowInstance(win));
				if (ret.isNotNull()) {
					::elm_win_autodel_set(win, EINA_TRUE);
					return ret;
				}

				::evas_object_del(win);

			}
			return sl_null;
		}
		
		static void _release_handle(Evas_Object* window)
		{
			::elm_win_lower(window);
			::evas_object_del(window);
		}

		void _release()
		{
			Evas_Object* window = m_window;
			if (window) {
				UIPlatform::removeWindowInstance(window);
				if (UI::isUiThread()) {
					_release_handle(window);
				} else {
					UI::dispatchToUiThread(Function<void()>::bind(&_release_handle, window));
				}
			}
			m_viewContent.setNull();
			m_window = sl_null;
		}
		
		Ref<ViewInstance> getContentView()
		{
			return m_viewContent;
		}
		
		void close()
		{
			Evas_Object* window = m_window;
			if (window) {
				if (!(UI::isUiThread())) {
					UI::dispatchToUiThread(SLIB_FUNCTION_WEAKREF(_Tizen_Window, close, this));
					return;
				}
				UIPlatform::removeWindowInstance(window);
				::elm_win_lower(window);
				::evas_object_del(window);
			}
			m_window = sl_null;
			m_viewContent.setNull();
		}
		
		sl_bool isClosed()
		{
			return m_window == sl_null;
		}
		
		sl_bool setParent(const Ref<WindowInstance>& window)
		{
			return sl_false;
		}
		
		sl_bool setFocus()
		{
			Evas_Object* window = m_window;
			if (window) {
				if (!(UI::isUiThread())) {
					UI::dispatchToUiThread(SLIB_BIND_WEAKREF(void(), _Tizen_Window, setFocus, this));
					return sl_true;
				}
				::elm_win_raise(window);
			}
			return sl_false;
		}
		
		UIRect getFrame()
		{
			return UIRect::zero();
		}
		
		sl_bool setFrame(const UIRect& _frame)
		{
			return sl_false;
		}
		
		UIRect getClientFrame()
		{
			return getFrame();
		}
		
		UISize getClientSize()
		{
			return getFrame().getSize();
		}
		
		sl_bool setClientSize(const UISize& _size)
		{
			return sl_false;
		}
		
		sl_bool setTitle(const String& title)
		{
			return sl_false;
		}
		
		sl_bool setBackgroundColor(const Color& _color)
		{
			return sl_false;
		}
		
		sl_bool isMinimized()
		{
			return sl_false;
		}
		
		sl_bool setMinimized(sl_bool flag)
		{
			return sl_false;
		}
		
		sl_bool isMaximized()
		{
			return sl_false;
		}
		
		sl_bool setMaximized(sl_bool flag)
		{
			return sl_false;
		}
		
		sl_bool setVisible(sl_bool flag)
		{
			Evas_Object* window = m_window;
			if (window) {
				if (!(UI::isUiThread())) {
					UI::dispatchToUiThread(SLIB_BIND_WEAKREF(void(), _Tizen_Window, setVisible, this, flag));
					return sl_true;
				}
				if (flag) {
					::evas_object_show(window);
				} else {
					::evas_object_hide(window);
				}
				return sl_true;
			} else {
				return sl_false;
			}
		}
		
		sl_bool setAlwaysOnTop(sl_bool flag)
		{
			return sl_false;
		}
		
		sl_bool setCloseButtonEnabled(sl_bool flag)
		{
			return sl_false;
		}
		
		sl_bool setMinimizeButtonEnabled(sl_bool flag)
		{
			return sl_false;
		}
		
		sl_bool setMaximizeButtonEnabled(sl_bool flag)
		{
			return sl_false;
		}
		
		sl_bool setResizable(sl_bool flag)
		{
			return sl_false;
		}
		
		sl_bool setAlpha(sl_real _alpha)
		{
			return sl_false;
		}
		
		sl_bool setTransparent(sl_bool flag)
		{
			return sl_false;
		}
		
		UIPointf convertCoordinateFromScreenToWindow(const UIPointf& ptScreen)
		{
			return ptScreen;
		}
		
		UIPointf convertCoordinateFromWindowToScreen(const UIPointf& ptWindow)
		{
			return ptWindow;
		}
		
		UIPointf convertCoordinateFromScreenToClient(const UIPointf& ptScreen)
		{
			return convertCoordinateFromScreenToWindow(ptScreen);
		}
		
		UIPointf convertCoordinateFromClientToScreen(const UIPointf& ptClient)
		{
			return convertCoordinateFromWindowToScreen(ptClient);
		}
		
		UIPointf convertCoordinateFromWindowToClient(const UIPointf& ptWindow)
		{
			return ptWindow;
		}
		
		UIPointf convertCoordinateFromClientToWindow(const UIPointf& ptClient)
		{
			return ptClient;
		}
		
		UISize getWindowSizeFromClientSize(const UISize& sizeClient)
		{
			return sizeClient;
		}
		
		UISize getClientSizeFromWindowSize(const UISize& sizeWindow)
		{
			return sizeWindow;
		}
		
	};
	
	
	Ref<WindowInstance> Window::createWindowInstance(const WindowInstanceParam& param)
	{
		return _Tizen_Window::create(param);
	}


	Ref<WindowInstance> UIPlatform::createWindowInstance(Evas_Object* window)
	{
		Ref<WindowInstance> ret = UIPlatform::_getWindowInstance(window);
		if (ret.isNotNull()) {
			return ret;
		}
		ret = _Tizen_Window::create(window);
		if (ret.isNotNull()) {
			UIPlatform::_registerWindowInstance(window, ret.get());
		}
		return ret;
	}
	
	Ref<WindowInstance> UIPlatform::getWindowInstance(Evas_Object* window)
	{
		return UIPlatform::_getWindowInstance(window);
	}
	
	void UIPlatform::removeWindowInstance(Evas_Object* window)
	{
		UIPlatform::_removeWindowInstance(window);
	}
	
	Evas_Object* UIPlatform::getWindowHandle(WindowInstance* instance)
	{
		_Tizen_Window* window = static_cast<_Tizen_Window*>(instance);
		if (window) {
			return window->m_window;
		} else {
			return sl_null;
		}
	}

}

#endif
