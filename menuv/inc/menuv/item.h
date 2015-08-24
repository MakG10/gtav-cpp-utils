#ifndef MENUV_ITEM_H_
#define MENUV_ITEM_H_

#include <string>
#include <vector>

#include "colors.h"

using namespace std;

enum MenuVItemType
{
	ACTION,
	TOGGLE,
	OPTION,
	OPTION_SET,
	KEYINPUT
};



class MenuVItem
{
public:
	string caption;
	string description;
	MenuVItemType type = ACTION;
	void(*callback) (MenuVItem*) = NULL;
	bool disabled = false;
	
	bool toggleValue = false;
	string optionValue;
	vector<string> optionSet;
	unsigned int optionSetActive = 0;
	int keyValue;
	string keyValueString;
	
	MenuVColor bgColor = COLOR_PRIMARY;
	MenuVColor textColor = COLOR_PRIMARY;
	

	MenuVItem(string caption);
	MenuVItem(string caption, MenuVItemType type, void(*callback) (MenuVItem*));

	void setCaption(string caption);
	string getCaption();
	
	void setDescription(string description);
	string getDescription();

	void setBgColor(MenuVColor color);
	MenuVColor getBgColor();

	void setTextColor(MenuVColor color);
	MenuVColor getTextColor();
	
	void setDisabled(bool disabled);
	bool isDisabled();

	void setOptionValue(string value);
	string getOptionValue();
	
	void setOptions(vector<string> options);
	vector<string> getOptions();
	void selectPrevOptionInSet();
	void selectNextOptionInSet();
	
	void setKeyValue(int value);
	int getKeyValue();
};

#endif
