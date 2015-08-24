/*
  Author: MakG (http://www.gta-mods.pl)
*/

#include <vector>
#include <string>

#include "../inc/menuv.h"
#include "../inc/menuv/template.h"
#include "../inc/keyboard.h"

#include "natives.h"
#include "types.h"
#include "enums.h"

using namespace std;
#pragma warning( disable : 4996 )

MenuV::MenuV()
{
	this->updateScreenResolution();
	//this->tpl = &menuvDefaultTemplate;
}

MenuV::MenuV(string headerText, void(*callback)(int, MenuVItem*))
{
	MenuV();

	this->headerText = headerText;
	this->callback = callback;
}

void MenuV::addItem(MenuVItem item)
{
	items.push_back(item);
}

void MenuV::addItem(string caption)
{
	MenuVItem newItem = MenuVItem(caption);

	items.push_back(newItem);
}

void MenuV::addItem(string caption, MenuVItemType type, void(*callback)(MenuVItem*))
{
	MenuVItem newItem = MenuVItem(caption, type, callback);

	items.push_back(newItem);
}

MenuVItem* MenuV::getItem(int index)
{
	return &this->items.at(index);
}

MenuVItem* MenuV::getItemByCaption(string caption)
{
	int i = 0;
	for(MenuVItem &item : this->items)
	{
		if(item.getCaption() == caption) return &this->items.at(i);
		i++;
	}
	
	return NULL;
}

void MenuV::setTemplate(MenuVTemplate* tpl)
{
	this->tpl = tpl;
}

MenuVTemplate MenuV::getTemplate()
{
	return *this->tpl;
}

void MenuV::setHeaderText(string text)
{
	this->headerText = text;
}

string MenuV::getHeaderText()
{
	return this->headerText;
}

void MenuV::draw()
{
	this->handleControls();
	
	//if (this->tpl == NULL)
	//{
		//MenuVTemplate defaultTemplate;
		//this->tpl = &defaultTemplate;
	//}
	
	this->tpl->setParams(this->headerText, this->headerBgColor, this->headerTextColor, this->activeItem);
	this->tpl->drawHeader();
	
	for (unsigned int i = 0; i < items.size(); i++)
	{
		MenuVItem item = items.at(i);

		tpl->drawItem(&item, i);
	}
}

void MenuV::drawMessage(string msg)
{
	UI::SET_TEXT_FONT(0);
	UI::SET_TEXT_SCALE(0.85f, 0.85f);
	UI::SET_TEXT_COLOUR(255, 255, 255, 255);
	UI::SET_TEXT_WRAP(0.0, 1.0);
	UI::SET_TEXT_CENTRE(1);
	UI::SET_TEXT_DROPSHADOW(2, 0, 0, 0, 255);
	UI::SET_TEXT_EDGE(1, 0, 0, 0, 205);
	UI::_SET_TEXT_ENTRY("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING((char *)msg.c_str());
	UI::_DRAW_TEXT(0.5, 0.5);
}

void MenuV::handleControls()
{
	if (this->tickCountInterval < GetTickCount())
	{
		if (IsKeyDown(VK_NUMPAD2) || CONTROLS::IS_CONTROL_PRESSED(2, 19))
		{
			this->playSound();

			this->activeItem = this->getNextActiveItem();

			this->tickCountInterval = GetTickCount() + 200;
		}

		if (IsKeyDown(VK_NUMPAD8) || CONTROLS::IS_CONTROL_PRESSED(2, 27))
		{
			this->playSound();

			this->activeItem = this->getPrevActiveItem();

			this->tickCountInterval = GetTickCount() + 200;
		}

		if (IsKeyDown(VK_NUMPAD5) || CONTROLS::IS_CONTROL_PRESSED(2, 18))
		{
			this->playSound();
			
			MenuVItem* selectedItem = &this->items.at(this->activeItem);
			this->callback(this->activeItem, selectedItem);

			string fetchedString;
			int fetchedKey;
			DWORD delay, interval;
			switch(selectedItem->type)
			{
				case TOGGLE:
					selectedItem->toggleValue = !selectedItem->toggleValue;
					break;
				
				case OPTION:
					
					interval = GetTickCount() + 300;
					while(!IsKeyDown(VK_RETURN))
					{
						if(fetchedString.empty())
						{
							this->drawMessage("TYPE IN THE VALUE AND PRESS ENTER");
						} else
						{
							this->drawMessage(fetchedString);
						}
						
						if(interval < GetTickCount())
						{
							int fetchKey = FetchKey();
							
							if(fetchKey != -1)
							{
								if (fetchKey == VK_BACK)
								{
									fetchedString = fetchedString.substr(0, fetchedString.size() - 1);
								} else {
									fetchedString = fetchedString + key2str(fetchKey);
								}
								
								interval = GetTickCount() + 400;
							}
						}

						WAIT(0);
					}
					
					selectedItem->setOptionValue(fetchedString);
					break;
				
				case KEYINPUT:
					fetchedKey = -1;
					
					delay = GetTickCount() + 400;
					while(fetchedKey == -1)
					{
						this->drawMessage("PRESS ANY KEY");
						
						if(delay < GetTickCount())
						{
							fetchedKey = FetchKeyUp();
						}
						
						WAIT(0);
					}
					
					this->playSound();
					
					selectedItem->setKeyValue(fetchedKey);
					break;
				
				default:
					break;
			}
			
			if(selectedItem->callback != NULL) selectedItem->callback(selectedItem);
			
			this->tickCountInterval = GetTickCount() + 200;
		}
		
		if (IsKeyDown(VK_NUMPAD4) || CONTROLS::IS_CONTROL_PRESSED(2, 15))
		{
			MenuVItem* activeItem = &this->items.at(this->activeItem);
			
			if(activeItem->type == OPTION_SET)
			{
				this->playSound();
				
				activeItem->selectPrevOptionInSet();
				
				if(activeItem->callback != NULL) activeItem->callback(activeItem);

				this->tickCountInterval = GetTickCount() + 200;
			}
		}
		
		if (IsKeyDown(VK_NUMPAD6) || CONTROLS::IS_CONTROL_PRESSED(2, 74))
		{
			MenuVItem* activeItem = &this->items.at(this->activeItem);
			
			if(activeItem->type == OPTION_SET)
			{
				this->playSound();
				
				activeItem->selectNextOptionInSet();
				
				if(activeItem->callback != NULL) activeItem->callback(activeItem);

				this->tickCountInterval = GetTickCount() + 200;
			}
		}

		if (IsKeyDown(VK_BACK) || CONTROLS::IS_CONTROL_PRESSED(2, 45))
		{
			this->playSound();
		}
	}
}

int MenuV::getPrevActiveItem()
{
	int activeItem = this->activeItem;
	
	for (unsigned int i = 0; i < this->items.size(); i++)
	{
		activeItem--;
		if(activeItem < 0) activeItem = (int)this->items.size() - 1;
		
		if(!this->items.at(activeItem).isDisabled()) break;
	}
	
	return activeItem;
}

int MenuV::getNextActiveItem()
{
	unsigned int activeItem = this->activeItem;
	
	for (unsigned int i = 0; i < this->items.size(); i++)
	{
		activeItem++;
		if(activeItem >= this->items.size()) activeItem = 0;
		
		if(!this->items.at(activeItem).isDisabled()) break;
	}
	
	return activeItem;
}

void MenuV::playSound()
{
// 	AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
}

float MenuV::scaleX(float value)
{
	if(screenWidth <= 0) this->updateScreenResolution();

	return value / screenWidth;
}

float MenuV::scaleY(float value)
{
	if (screenHeight <= 0) this->updateScreenResolution();

	return value / screenHeight;
}

void MenuV::updateScreenResolution()
{
	//int width, height;
	//GRAPHICS::_GET_SCREEN_ACTIVE_RESOLUTION(&width, &height);

	this->screenWidth = (float)1280;
	this->screenHeight = (float)720;
}
