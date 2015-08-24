#ifndef MENUV_TEMPLATE_H_
#define MENUV_TEMPLATE_H_

#include "../../inc/menuv/item.h"
#include "../../inc/menuv.h"

//class MenuV;

class MenuVTemplate
{
public:

	MenuVColorRGBA bgPrimaryColor;
	MenuVColorRGBA bgSecondaryColor;
	
	MenuVColorRGBA textPrimaryColor;
	MenuVColorRGBA textSecondaryColor;
	
	MenuVColorRGBA highlightedBgPrimaryColor;
	MenuVColorRGBA highlightedBgSecondaryColor;
	
	MenuVColorRGBA highlightedTextPrimaryColor;
	MenuVColorRGBA highlightedTextSecondaryColor;

	MenuVColorRGBA disabledBgPrimaryColor;
	MenuVColorRGBA disabledBgSecondaryColor;

	MenuVColorRGBA disabledTextPrimaryColor;
	MenuVColorRGBA disabledTextSecondaryColor;
	
	MenuVColorRGBA headerBgPrimaryColor;
	MenuVColorRGBA headerBgSecondaryColor;
	
	MenuVColorRGBA headerTextPrimaryColor;
	MenuVColorRGBA headerTextSecondaryColor;

	string paramHeaderText;
	MenuVColor paramHeaderBgColor;
	MenuVColor paramHeaderTextColor;
	int paramActiveItem;

	
	MenuVTemplate();
	virtual ~MenuVTemplate() {};
	
	virtual void drawHeader();
	virtual void drawItem(MenuVItem* item, int index);
	
	void setParams(string paramHeaderText, MenuVColor paramHeaderBgColor, MenuVColor paramHeaderTextColor, int paramActiveItem);
	
	float scaleX(float value);
	float scaleY(float value);
	
	string getToggleText(bool toggle);
	
private:
	float marginLeft = scaleX(15.0);
	float marginTop = scaleY(15.0);
};

#endif