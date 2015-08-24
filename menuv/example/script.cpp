/*
  Author: MakG (http://www.gta-mods.pl)
*/

#include "script.h"
#include "keyboard.h"

#include "menuv.h"
#include "menuv/template/gtamodspl.h"

using namespace std;

MenuV menu;
MenuVTemplate menuTemplate1;
MenuVTemplateGtaModsPl menuTemplate2;

// Opcje ustawiane w menu
int menuKey = str2key("F6");
bool menuSlowMotion = true;
int menuSlowMotionValue = 30;


void MenuVExampleMain()
{
	srand(GetTickCount());
	main();
}

void main()
{
	createMenu();

	bool menuState = false;
	bool slowMotionState = false;
	DWORD inputWait = 0;

	while (true)
	{
		if (IsKeyDown(menuKey) && inputWait < GetTickCount())
		{
			menuState = !menuState;
			inputWait = GetTickCount() + 500;
		}

		if (menuState)
		{
			menu.draw();

			if (menuSlowMotion)
			{
				GAMEPLAY::SET_TIME_SCALE(menuSlowMotionValue / 100.0f);
				slowMotionState = true;
			}
			else if (slowMotionState)
			{
				GAMEPLAY::SET_TIME_SCALE(1.0f);
				slowMotionState = false;
			}
		}
		else if (slowMotionState)
		{
			GAMEPLAY::SET_TIME_SCALE(1.0f); // przywrocenie predkosci gry (raz)
			slowMotionState = false;
		}

		WAIT(0);
	}
}

void createMenu()
{
	menu = MenuV("MenuV by MakG", MenuCallbacks::other);
	menu.setTemplate(&menuTemplate2);
	
	// Skrot klawiszowy do menu
	MenuVItem shortcutItem = MenuVItem("Klawisz otwierajacy menu", KEYINPUT, MenuCallbacks::shortcut);
	shortcutItem.setKeyValue(menuKey);
	shortcutItem.setBgColor(COLOR_PRIMARY);
	menu.addItem(shortcutItem);
	
	// Zaznaczenie wszystkich ON/OFF
	MenuVItem slowMotionItem = MenuVItem("Spowolnienie czasu w menu", TOGGLE, MenuCallbacks::slowMotion);
	slowMotionItem.toggleValue = menuSlowMotion;
	slowMotionItem.setBgColor(COLOR_PRIMARY);
	menu.addItem(slowMotionItem);
	
	// Limit celi do zaznaczenia, 0 - bez limitu, to samo jezeli zostanie wprowadzony tekst, zamiast liczby
	MenuVItem slowMotionValueItem = MenuVItem("Predkosc gry w menu (0-100)", OPTION, MenuCallbacks::slowMotionValue);
	slowMotionValueItem.optionValue = to_string(menuSlowMotionValue);
	slowMotionValueItem.setBgColor(COLOR_PRIMARY);
	menu.addItem(slowMotionValueItem);
	
	// Kamery egzekucji
	MenuVItem styleItem = MenuVItem("Styl menu", OPTION_SET, MenuCallbacks::style);
	styleItem.setOptions({ "Domyslny", "gta-mods.pl" });
	styleItem.optionValue = "gta-mods.pl";
	styleItem.setBgColor(COLOR_SECONDARY);
	menu.addItem(styleItem);
}

void MenuCallbacks::shortcut(MenuVItem* item)
{
	menuKey = item->getKeyValue();
}

void MenuCallbacks::slowMotion(MenuVItem* item)
{
	menuSlowMotion = item->toggleValue;
}

void MenuCallbacks::slowMotionValue(MenuVItem* item)
{
	int value = stoi(item->optionValue);

	if (value < 0)
	{
		menuSlowMotionValue = 0;
		item->optionValue = "0";
	}
	else if (value > 100)
	{
		menuSlowMotionValue = 100;
		item->optionValue = "100";
	} else {
		menuSlowMotionValue = value;
		item->optionValue = to_string(value);
	}
}

void MenuCallbacks::style(MenuVItem* item)
{
	if (item->getOptionValue() == "gta-mods.pl")
	{
		menu.setTemplate(&menuTemplate2);
	} else {
		menu.setTemplate(&menuTemplate1);
	}
}

void MenuCallbacks::other(int index, MenuVItem* item)
{
	// domyslna obsluga innych pozycji menu
}
