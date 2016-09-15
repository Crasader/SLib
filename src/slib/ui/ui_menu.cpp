#include "../../../inc/slib/ui/menu.h"

SLIB_UI_NAMESPACE_BEGIN

SLIB_DEFINE_OBJECT(MenuItem, Object)

MenuItem::MenuItem()
{
	m_flagEnabled = sl_true;
	m_flagChecked = sl_false;
}

Ref<Menu> MenuItem::getParent() const
{
	return m_parent;
}

String MenuItem::getText() const
{
	return m_text;
}

void MenuItem::setText(const String& text)
{
	m_text = text;
}

const KeycodeAndModifiers& MenuItem::getShortcutKey() const
{
	return m_shortcutKey;
}

void MenuItem::setShortcutKey(const KeycodeAndModifiers& km)
{
	m_shortcutKey = km;
}

const KeycodeAndModifiers& MenuItem::getSecondShortcutKey() const
{
	return m_secondShortcutKey;
}

void MenuItem::setSecondShortcutKey(const KeycodeAndModifiers& km)
{
	m_secondShortcutKey = km;
}

sl_bool MenuItem::isEnabled() const
{
	return m_flagEnabled;
}

void MenuItem::setEnabled(sl_bool flag)
{
	m_flagEnabled = flag;
}

sl_bool MenuItem::isChecked() const
{
	return m_flagChecked;
}

void MenuItem::setChecked(sl_bool flag)
{
	m_flagChecked = flag;
}

Ref<Bitmap> MenuItem::getIcon() const
{
	return m_icon;
}

void MenuItem::setIcon(const Ref<Bitmap>& icon)
{
	m_icon = icon;
}

Ref<Bitmap> MenuItem::getCheckedIcon() const
{
	return m_checkedIcon;
}

void MenuItem::setCheckedIcon(const Ref<Bitmap>& icon)
{
	m_checkedIcon = icon;
}

Ref<Menu> MenuItem::getSubmenu() const
{
	return m_submenu;
}

void MenuItem::setSubmenu(const Ref<Menu>& menu)
{
	m_submenu = menu;
}

Ref<Runnable> MenuItem::getAction() const
{
	return m_action;
}

void MenuItem::setAction(const Ref<Runnable>& action)
{
	m_action = action;
}

sl_bool MenuItem::isSeparator() const
{
	return sl_false;
}

class _MenuItemSeparator : public MenuItem
{
public:
	// override
	sl_bool isSeparator() const
	{
		return sl_true;
	}

};

Ref<MenuItem> MenuItem::createSeparator()
{
	return new _MenuItemSeparator;
}


MenuItemParam::MenuItemParam()
{
	flagEnabled = sl_true;
	flagChecked = sl_false;
}

SLIB_DEFINE_OBJECT(Menu, Object)

Menu::Menu()
{
}

sl_uint32 Menu::getMenuItemsCount() const
{
	return (sl_uint32)(m_items.getCount());
}

Ref<MenuItem> Menu::getMenuItem(sl_uint32 index) const
{
	return m_items.getItemValue(index, Ref<MenuItem>::null());
}

void Menu::show(const UIPoint& pt)
{
	show(pt.x, pt.y);
}

Ref<MenuItem> Menu::addMenuItem(const String& title)
{
	MenuItemParam param;
	param.text = title;
	return addMenuItem(param);
}

Ref<MenuItem> Menu::addMenuItem(const String& title, const Ref<Bitmap>& icon)
{
	MenuItemParam param;
	param.text = title;
	param.icon = icon;
	return addMenuItem(param);
}

Ref<MenuItem> Menu::addMenuItem(const String& title, const Ref<Bitmap>& icon, const Ref<Bitmap>& checkedIcon)
{
	MenuItemParam param;
	param.text = title;
	param.icon = icon;
	param.checkedIcon = checkedIcon;
	return addMenuItem(param);
}

Ref<MenuItem> Menu::addMenuItem(const String& title, const KeycodeAndModifiers& shortcutKey)
{
	MenuItemParam param;
	param.text = title;
	param.shortcutKey = shortcutKey;
	return addMenuItem(param);
}

Ref<MenuItem> Menu::addMenuItem(const String& title, const KeycodeAndModifiers& shortcutKey, const Ref<Bitmap>& icon)
{
	MenuItemParam param;
	param.text = title;
	param.shortcutKey = shortcutKey;
	param.icon = icon;
	return addMenuItem(param);
}

Ref<MenuItem> Menu::addMenuItem(const String& title, const KeycodeAndModifiers& shortcutKey, const Ref<Bitmap>& icon, const Ref<Bitmap>& checkedIcon)
{
	MenuItemParam param;
	param.text = title;
	param.shortcutKey = shortcutKey;
	param.icon = icon;
	param.checkedIcon = checkedIcon;
	return addMenuItem(param);
}

Ref<MenuItem> Menu::addSubmenu(Ref<Menu>& submenu, const String& title)
{
	MenuItemParam param;
	param.text = title;
	param.submenu = submenu;
	return addMenuItem(param);
}

Ref<MenuItem> Menu::addSubmenu(Ref<Menu>& submenu, const String& title, const Ref<Bitmap>& icon)
{
	MenuItemParam param;
	param.text = title;
	param.icon = icon;
	param.submenu = submenu;
	return addMenuItem(param);
}

Ref<MenuItem> Menu::addSubmenu(Ref<Menu>& submenu, const String& title, const Ref<Bitmap>& icon, const Ref<Bitmap>& checkedIcon)
{
	MenuItemParam param;
	param.text = title;
	param.icon = icon;
	param.checkedIcon = checkedIcon;
	param.submenu = submenu;
	return addMenuItem(param);
}

SLIB_UI_NAMESPACE_END