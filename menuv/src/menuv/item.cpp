#include "../../inc/menuv/item.h"
#include "../../inc/keyboard.h"

MenuVItem::MenuVItem(string caption)
{
	this->caption = caption;
}

MenuVItem::MenuVItem(string caption, MenuVItemType type, void(*callback) (MenuVItem*))
{
	this->caption = caption;
	this->type = type;
	this->callback = callback;
}

void MenuVItem::setCaption(string caption)
{
	this->caption = caption;
}

string MenuVItem::getCaption()
{
	return this->caption;
}

void MenuVItem::setDescription(string description)
{
	this->description = description;
}

string MenuVItem::getDescription()
{
	return this->description;
}

void MenuVItem::setBgColor(MenuVColor color)
{
	this->bgColor = color;
}

MenuVColor MenuVItem::getBgColor()
{
	return this->bgColor;
}

void MenuVItem::setTextColor(MenuVColor color)
{
	this->textColor = color;
}

MenuVColor MenuVItem::getTextColor()
{
	return this->textColor;
}

void MenuVItem::setDisabled(bool disabled)
{
	this->disabled = disabled;
}

bool MenuVItem::isDisabled()
{
	return this->disabled;
}

void MenuVItem::setOptionValue(string value)
{
	this->optionValue = value;
}

string MenuVItem::getOptionValue()
{
	return this->optionValue;
}

void MenuVItem::setOptions(vector<string> options)
{
	this->optionSet = options;
	this->optionValue = options.at(0);
}

vector<string> MenuVItem::getOptions()
{
	return this->optionSet;
}

void MenuVItem::selectPrevOptionInSet()
{
	this->optionSetActive--;
	if(this->optionSetActive < 0) this->optionSetActive = (int)this->optionSet.size() - 1;
	
	this->optionValue = this->optionSet.at(this->optionSetActive);
}

void MenuVItem::selectNextOptionInSet()
{
	this->optionSetActive++;
	if(this->optionSetActive >= this->optionSet.size()) this->optionSetActive = 0;
	
	this->optionValue = this->optionSet.at(this->optionSetActive);
}

void MenuVItem::setKeyValue(int value)
{
	this->keyValue = value;
	this->keyValueString = key2str(value);
}

int MenuVItem::getKeyValue()
{
	return this->keyValue;
}
