#pragma once

#include <string>

#include "natives.h"
#include "types.h"
#include "enums.h"

#include "main.h"

#include "menuv/item.h"

void MenuVExampleMain();
void main();
void createMenu();

class MenuCallbacks
{
public:
	static void shortcut(MenuVItem* item);
	static void slowMotion(MenuVItem* item);
	static void slowMotionValue(MenuVItem* item);
	static void style(MenuVItem* item);

	static void other(int index, MenuVItem* item);
};