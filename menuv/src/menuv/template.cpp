#include "../../inc/menuv/colors.h"
#include "../../inc/menuv/template.h"

#include "natives.h"
#include "types.h"
#include "enums.h"

MenuVTemplate::MenuVTemplate()
{
	this->bgPrimaryColor = MenuVColorRGBA(56, 95, 94, 210);
	this->bgSecondaryColor = MenuVColorRGBA(30, 70, 65, 210);
	
	this->textPrimaryColor = MenuVColorRGBA(243, 255, 255, 255);
	this->textSecondaryColor = MenuVColorRGBA(243, 255, 255, 255);
	
	this->highlightedBgPrimaryColor = MenuVColorRGBA(218, 242, 216, 255);
	this->highlightedBgSecondaryColor = MenuVColorRGBA(255, 255, 255, 255);
	
	this->highlightedTextPrimaryColor = MenuVColorRGBA(10, 10, 10, 255);
	this->highlightedTextSecondaryColor = MenuVColorRGBA(255, 255, 255, 255);

	this->disabledBgPrimaryColor = MenuVColorRGBA(100, 100, 100, 180);
	this->disabledBgSecondaryColor = MenuVColorRGBA(100, 100, 100, 180);

	this->disabledTextPrimaryColor = MenuVColorRGBA(180, 180, 180, 255);
	this->disabledTextSecondaryColor = MenuVColorRGBA(180, 180, 180, 255);
	
	this->headerBgPrimaryColor = MenuVColorRGBA(10, 10, 10, 255);
	this->headerBgSecondaryColor = MenuVColorRGBA(236, 236, 236, 255);
	
	this->headerTextPrimaryColor = MenuVColorRGBA(245, 245, 245, 255);
	this->headerTextSecondaryColor = MenuVColorRGBA(10, 10, 10, 255);
}

void MenuVTemplate::drawHeader()
{
	if(!this->paramHeaderText.empty())
	{
		MenuVColorRGBA textColor = this->paramHeaderTextColor == COLOR_PRIMARY ? this->headerTextPrimaryColor : this->headerTextSecondaryColor;
		MenuVColorRGBA bgColor = this->paramHeaderBgColor == COLOR_PRIMARY ? this->headerBgPrimaryColor : this->headerBgSecondaryColor;
	
		float width = scaleX(400.0);
		float height = scaleY(45.0);
		
		GRAPHICS::DRAW_RECT(marginLeft + width * 0.5f, marginTop + height * 0.5f, width, height, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
		
		UI::SET_TEXT_FONT(1);
		UI::SET_TEXT_SCALE(0.0, 0.6f);
		UI::SET_TEXT_COLOUR(textColor.r, textColor.g, textColor.b, textColor.a);
		UI::SET_TEXT_CENTRE(0);
		UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
		UI::SET_TEXT_EDGE(0, 0, 0, 0, 0);
		UI::_SET_TEXT_ENTRY("STRING");
		UI::_ADD_TEXT_COMPONENT_STRING((LPSTR)this->paramHeaderText.c_str());
		UI::_DRAW_TEXT(marginLeft + scaleX(4.0), marginTop + scaleY(10.0));
	}
}

void MenuVTemplate::drawItem(MenuVItem* item, int index)
{
	bool isActive = (index == this->paramActiveItem);
	float marginTop = this->paramHeaderText.empty() ? this->marginTop : this->marginTop + scaleY(45.0f);
	
	MenuVColorRGBA textColor;
	MenuVColorRGBA bgColor;
	if (isActive)
	{
		textColor = item->textColor == COLOR_PRIMARY ? this->highlightedTextPrimaryColor : this->highlightedTextSecondaryColor;
		bgColor = item->bgColor == COLOR_PRIMARY ? this->highlightedBgPrimaryColor : this->highlightedBgSecondaryColor;
	}
	else if (item->isDisabled())
	{
		textColor = item->textColor == COLOR_PRIMARY ? this->disabledTextPrimaryColor : this->disabledTextSecondaryColor;
		bgColor = item->bgColor == COLOR_PRIMARY ? this->disabledBgPrimaryColor : this->disabledBgSecondaryColor;
	} else {
		textColor = item->textColor == COLOR_PRIMARY ? this->textPrimaryColor : this->textSecondaryColor;
		bgColor = item->bgColor == COLOR_PRIMARY ? this->bgPrimaryColor : this->bgSecondaryColor;
	}
	
	float width = scaleX(400.0);
	float height = scaleY(35.0);
	
	// Rysowanie
	
	GRAPHICS::DRAW_RECT(marginLeft + width * 0.5f, marginTop + height * 0.5f + index * height, width, height, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
	
	UI::SET_TEXT_FONT(0);
	UI::SET_TEXT_SCALE(0.0, 0.4f);
	UI::SET_TEXT_COLOUR(textColor.r, textColor.g, textColor.b, textColor.a);
	UI::SET_TEXT_CENTRE(0);
	UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
	UI::SET_TEXT_EDGE(0, 0, 0, 0, 0);
	UI::_SET_TEXT_ENTRY("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING((LPSTR)item->getCaption().c_str());
	UI::_DRAW_TEXT(marginLeft + scaleX(4.0), marginTop + height * index + scaleY(6.0));
	
	string extraText;
	switch(item->type)
	{
		case TOGGLE:
			extraText = this->getToggleText(item->toggleValue);
			break;
			
		case OPTION:
			extraText = item->optionValue;
			break;
			
		case OPTION_SET:
			extraText = "< " + item->optionValue + " >";
			break;

		case KEYINPUT:
			extraText = item->keyValueString;
			break;
			
		default:
			break;
	}
	
	if(!extraText.empty())
	{
		UI::SET_TEXT_FONT(0);
		UI::SET_TEXT_SCALE(0.0, 0.4f);
		UI::SET_TEXT_COLOUR(textColor.r, textColor.g, textColor.b, textColor.a);
		UI::SET_TEXT_RIGHT_JUSTIFY(1);
		UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
		UI::SET_TEXT_EDGE(0, 0, 0, 0, 0);
		UI::SET_TEXT_WRAP(marginLeft, marginLeft + width - scaleX(4.0));
		UI::_SET_TEXT_ENTRY("STRING");
		UI::_ADD_TEXT_COMPONENT_STRING((LPSTR)extraText.c_str());
		UI::_DRAW_TEXT(0.0, marginTop + height * index + scaleY(4.0f));
	}
}

void MenuVTemplate::setParams(string paramHeaderText, MenuVColor paramHeaderBgColor, MenuVColor paramHeaderTextColor, int paramActiveItem)
{
	this->paramHeaderText = paramHeaderText;
	this->paramHeaderBgColor = paramHeaderBgColor;
	this->paramHeaderTextColor = paramHeaderTextColor;
	this->paramActiveItem = paramActiveItem;
}
float MenuVTemplate::scaleX(float value)
{
	return value / 1280.0f;
}

float MenuVTemplate::scaleY(float value)
{
	return value / 720.0f;
}

string MenuVTemplate::getToggleText(bool toggle)
{
	return toggle ? "ON" : "OFF";
}