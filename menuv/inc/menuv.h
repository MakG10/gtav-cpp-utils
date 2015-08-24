#ifndef MENUV_H_
#define MENUV_H_

#include <vector>
#include <string>
#include <ctime>
#include <Windows.h>

#include "menuv/item.h"
#include "menuv/template.h"
#include "menuv/colors.h"

using namespace std;



class MenuV
{
	vector<MenuVItem> items;
	void(*callback) (int, MenuVItem*);
	
	class MenuVTemplate* tpl = NULL;

	DWORD tickCountInterval = 0;

public:
	int activeItem = 0;

	string headerText;
	MenuVColor headerBgColor = COLOR_PRIMARY;
	MenuVColor headerTextColor = COLOR_PRIMARY;
	
	float screenWidth = 0;
	float screenHeight = 0;

public:

	MenuV();
	MenuV(string header, void(*callback)(int, MenuVItem*));
	
	void addItem(MenuVItem item);
	void addItem(string caption);
	void addItem(string caption, MenuVItemType type, void(*callback)(MenuVItem*));
	
	MenuVItem* getItem(int index);
	MenuVItem* getItemByCaption(string caption);
	
	void setTemplate(class MenuVTemplate* tpl);
	MenuVTemplate getTemplate();
	
	void setHeaderText(string text);
	string getHeaderText();
	
	void setHeaderBgColor(MenuVColor color);
	MenuVColor getHeaderBgColor();
	
	void setHeaderTextColor(MenuVColor color);
	MenuVColor getHeaderTextColor();

	void draw();
	void drawMessage(string msg);

	float scaleX(float value);
	float scaleY(float value);

private:

	void handleControls();

	int getPrevActiveItem();
	int getNextActiveItem();

	void playSound();

	void updateScreenResolution();
};

#endif
