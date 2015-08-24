/*
		THIS FILE IS A PART OF GTA V SCRIPT HOOK SDK
					http://dev-c.com
				(C) Alexander Blade 2015
*/

/*
        MODIFICATIONS MADE by MakG
		  http://www.gta-mods.pl
*/

#include <map>
#include <vector>
#include <string>
#include <sstream>

#include "../inc/keyboard.h"
#include "natives.h"

const int KEYS_SIZE = 255;
const int NOW_PERIOD = 100, MAX_DOWN = 5000; // ms

struct {
	DWORD time;
	BOOL isWithAlt;
	BOOL wasDownBefore;
	BOOL isUpNow;
} keyStates[KEYS_SIZE];

int lastKeyPress = -1;

void OnKeyboardMessage(DWORD key, WORD repeats, BYTE scanCode, BOOL isExtended, BOOL isWithAlt, BOOL wasDownBefore, BOOL isUpNow)
{
	if (key < KEYS_SIZE)
	{
		keyStates[key].time = GetTickCount();
		keyStates[key].isWithAlt = isWithAlt;
		keyStates[key].wasDownBefore = wasDownBefore;
		keyStates[key].isUpNow = isUpNow;
		
		lastKeyPress = (int) key;
	}
}

bool IsKeyDown(DWORD key)
{
	return (key < KEYS_SIZE) ? ((GetTickCount() < keyStates[key].time + MAX_DOWN) && !keyStates[key].isUpNow) : false;
}

bool IsKeyJustUp(DWORD key, bool exclusive)
{
	bool b = (key < KEYS_SIZE) ? (GetTickCount() < keyStates[key].time + NOW_PERIOD && keyStates[key].isUpNow) : false;
	if (b && exclusive)
		ResetKeyState(key);
	return b;
}

void ResetKeyState(DWORD key)
{
	if (key < KEYS_SIZE)
		memset(&keyStates[key], 0, sizeof(keyStates[0]));
}

int FetchKey()
{
	if(lastKeyPress != -1)
	{
		if(GetTickCount() < keyStates[lastKeyPress].time + NOW_PERIOD)
		{
			return lastKeyPress;
		}
	}
	
	return -1;
}

int FetchKeyUp()
{
	if (lastKeyPress != -1)
	{
		if (GetTickCount() < keyStates[lastKeyPress].time + NOW_PERIOD && keyStates[lastKeyPress].isUpNow)
		{
			return lastKeyPress;
		}
	}

	return -1;
}

bool IsKeyCombinationDown(std::string humanReadableKey)
{
	std::vector<std::string> keys = SplitKeyCombination(humanReadableKey);

	bool allPressed = true;
	for (auto &key : keys)
	{
		if (!IsKeyDown(str2key(key)))
		{
			allPressed = false;
			break;
		}
	}

	return allPressed;
}

void PressKeyCombination(std::vector<int> keys)
{
	INPUT Event;

	for (auto &key : keys)
	{
		const UINT mappedKey = MapVirtualKey(LOBYTE(key), 0);
		Event.type = INPUT_KEYBOARD;
		Event.ki.dwFlags = KEYEVENTF_SCANCODE;
		Event.ki.wScan = mappedKey;
		SendInput(1, &Event, sizeof(Event));

		WAIT(101);
	}

	for (auto &key : keys)
	{
		const UINT mappedKey = MapVirtualKey(LOBYTE(key), 0);

		Event.type = INPUT_KEYBOARD;
		Event.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
		Event.ki.wScan = mappedKey;
		SendInput(1, &Event, sizeof(Event));

		WAIT(101);
	}
}

void PressKeyCombination(std::vector<std::string> humanReadableKeys)
{
	std::vector<int> keys;
	for (auto &key : humanReadableKeys)
	{
		keys.push_back(str2key(key));
	}

	PressKeyCombination(keys);
}

void PressKey(std::string humanReadableKey)
{
	std::vector<std::string> keys = SplitKeyCombination(humanReadableKey);

	PressKeyCombination(keys);
}

std::vector<std::string> SplitKeyCombination(std::string humanReadableKey)
{
	std::vector<std::string> keys;
	//boost::split(keys, humanReadableKey, boost::is_any_of("+"));
	
	std::stringstream ss(humanReadableKey);
	std::string key;
	while (std::getline(ss, key, '+'))
	{
		keys.push_back(key);
	}
	
	return keys;
}

DWORD str2key(std::string humanReadableKey)
{
	std::map <std::string, int> keymap;

	keymap["LMB"] = VK_LBUTTON;
	keymap["RMB"] = VK_RBUTTON;
	keymap["CANCEL"] = VK_CANCEL;
	keymap["MMB"] = VK_MBUTTON;
	keymap["BACKSPACE"] = VK_BACK;
	keymap["TAB"] = VK_TAB;
	keymap["CLEAR"] = VK_CLEAR;
	keymap["RETURN"] = VK_RETURN;
	keymap["SHIFT"] = VK_SHIFT;
	keymap["CTRL"] = VK_CONTROL;
	keymap["ALT"] = VK_MENU;
	keymap["PAUSE"] = VK_PAUSE;
	keymap["CAPSLOCK"] = VK_CAPITAL;
	keymap["ESCAPE"] = VK_ESCAPE;
	keymap["SPACE"] = VK_SPACE;
	keymap["PAGEUP"] = VK_PRIOR;
	keymap["PAGEDOWN"] = VK_NEXT;
	keymap["END"] = VK_END;
	keymap["HOME"] = VK_HOME;
	keymap["LEFT"] = VK_LEFT;
	keymap["UP"] = VK_UP;
	keymap["RIGHT"] = VK_RIGHT;
	keymap["DOWN"] = VK_DOWN;
	keymap["SELECT"] = VK_SELECT;
	keymap["PRINT"] = VK_PRINT;
	keymap["EXECUTE"] = VK_EXECUTE;
	keymap["PRINTSCREEN"] = VK_SNAPSHOT;
	keymap["INSERT"] = VK_INSERT;
	keymap["DELETE"] = VK_DELETE;
	keymap["HELP"] = VK_HELP;
	keymap["LWIN"] = VK_LWIN;
	keymap["RWIN"] = VK_RWIN;
	keymap["APPS"] = VK_APPS;
	keymap["SLEEP"] = VK_SLEEP;
	keymap["NUM0"] = VK_NUMPAD0;
	keymap["NUM1"] = VK_NUMPAD1;
	keymap["NUM2"] = VK_NUMPAD2;
	keymap["NUM3"] = VK_NUMPAD3;
	keymap["NUM4"] = VK_NUMPAD4;
	keymap["NUM5"] = VK_NUMPAD5;
	keymap["NUM6"] = VK_NUMPAD6;
	keymap["NUM7"] = VK_NUMPAD7;
	keymap["NUM8"] = VK_NUMPAD8;
	keymap["NUM9"] = VK_NUMPAD9;
	keymap["*"] = VK_MULTIPLY;
	keymap["PLUS"] = VK_ADD;
// 	keymap[","] = VK_SEPARATOR;
	keymap["-"] = VK_SUBTRACT;
	keymap["."] = VK_DECIMAL;
	keymap["/"] = VK_DIVIDE;
	keymap["F1"] = VK_F1;
	keymap["F2"] = VK_F2;
	keymap["F3"] = VK_F3;
	keymap["F4"] = VK_F4;
	keymap["F5"] = VK_F5;
	keymap["F6"] = VK_F6;
	keymap["F7"] = VK_F7;
	keymap["F8"] = VK_F8;
	keymap["F9"] = VK_F9;
	keymap["F10"] = VK_F10;
	keymap["F11"] = VK_F11;
	keymap["F12"] = VK_F12;
	keymap["F13"] = VK_F13;
	keymap["F14"] = VK_F14;
	keymap["F15"] = VK_F15;
	keymap["F16"] = VK_F16;
	keymap["F17"] = VK_F17;
	keymap["F18"] = VK_F18;
	keymap["F19"] = VK_F19;
	keymap["F20"] = VK_F20;
	keymap["F21"] = VK_F21;
	keymap["F22"] = VK_F22;
	keymap["F23"] = VK_F23;
	keymap["F24"] = VK_F24;
	keymap["NUMLOCK"] = VK_NUMLOCK;
	keymap["SCROLL"] = VK_SCROLL;
	keymap["SHIFT"] = VK_LSHIFT;
	keymap["RSHIFT"] = VK_RSHIFT;
	keymap["LCTRL"] = VK_LCONTROL;
	keymap["RCTRL"] = VK_RCONTROL;
	keymap["LMENU"] = VK_LMENU;
	keymap["RMENU"] = VK_RMENU;
	keymap["BROWSER_BACK"] = VK_BROWSER_BACK;
	keymap["BROWSER_FORWARD"] = VK_BROWSER_FORWARD;
	keymap["BROWSER_REFRESH"] = VK_BROWSER_REFRESH;
	keymap["BROWSER_STOP"] = VK_BROWSER_STOP;
	keymap["BROWSER_SEARCH"] = VK_BROWSER_SEARCH;
	keymap["BROWSER_FAVORITES"] = VK_BROWSER_FAVORITES;
	keymap["BROWSER_HOME"] = VK_BROWSER_HOME;
	keymap["VOLUME_MUTE"] = VK_VOLUME_MUTE;
	keymap["VOLUME_DOWN"] = VK_VOLUME_DOWN;
	keymap["VOLUME_UP"] = VK_VOLUME_UP;
	keymap["MEDIA_NEXT_TRACK"] = VK_MEDIA_NEXT_TRACK;
	keymap["MEDIA_PREV_TRACK"] = VK_MEDIA_PREV_TRACK;
	keymap["MEDIA_STOP"] = VK_MEDIA_STOP;
	keymap["MEDIA_PLAY_PAUSE"] = VK_MEDIA_PLAY_PAUSE;
	keymap["LAUNCH_MAIL"] = VK_LAUNCH_MAIL;
	keymap["LAUNCH_MEDIA_SELECT"] = VK_LAUNCH_MEDIA_SELECT;
	keymap["LAUNCH_APP1"] = VK_LAUNCH_APP1;
	keymap["LAUNCH_APP2"] = VK_LAUNCH_APP2;
	keymap["PLAY"] = VK_PLAY;
	keymap["ZOOM"] = VK_ZOOM;
	keymap[";"] = VK_OEM_1;
	keymap[":"] = VK_OEM_1;
	keymap[","] = VK_OEM_COMMA;
	keymap["~"] = VK_OEM_3;
	keymap["["] = VK_OEM_4;
	keymap["]"] = VK_OEM_6;
	keymap["\\"] = VK_OEM_5;

	if (keymap.find(humanReadableKey) != keymap.end())
	{
		return keymap[humanReadableKey];
	}

	if (humanReadableKey.length() == 1)
	{
		char letter = humanReadableKey.c_str()[0];

		if ((letter >= 0x30 && letter <= 0x39) || (letter >= 0x41 && letter <= 0x5A))
		{
			return (int)letter;
		}
	}

	if (humanReadableKey.length() == 2 || humanReadableKey.length() == 3)
	{
		try {
			int key = std::stoi(humanReadableKey);
			return key;
		} catch (...) {
			return -1;
		}
	}

	return -1;
}

std::string key2str(DWORD key)
{
	std::map <int, std::string> keymap;

	keymap[VK_LBUTTON] = "LMB";
	keymap[VK_RBUTTON] = "RMB";
	keymap[VK_CANCEL] = "CANCEL";
	keymap[VK_MBUTTON] = "MMB";
	keymap[VK_BACK] = "BACKSPACE";
	keymap[VK_TAB] = "TAB";
	keymap[VK_CLEAR] = "CLEAR";
	keymap[VK_RETURN] = "RETURN";
	keymap[VK_SHIFT] = "SHIFT";
	keymap[VK_CONTROL] = "CTRL";
	keymap[VK_MENU] = "ALT";
	keymap[VK_PAUSE] = "PAUSE";
	keymap[VK_CAPITAL] = "CAPSLOCK";
	keymap[VK_ESCAPE] = "ESCAPE";
	keymap[VK_SPACE] = "SPACE";
	keymap[VK_PRIOR] = "PAGEUP";
	keymap[VK_NEXT] = "PAGEDOWN";
	keymap[VK_END] = "END";
	keymap[VK_HOME] = "HOME";
	keymap[VK_LEFT] = "LEFT";
	keymap[VK_UP] = "UP";
	keymap[VK_RIGHT] = "RIGHT";
	keymap[VK_DOWN] = "DOWN";
	keymap[VK_SELECT] = "SELECT";
	keymap[VK_PRINT] = "PRINT";
	keymap[VK_EXECUTE] = "EXECUTE";
	keymap[VK_SNAPSHOT] = "PRINTSCREEN";
	keymap[VK_INSERT] = "INSERT";
	keymap[VK_DELETE] = "DELETE";
	keymap[VK_HELP] = "HELP";
	keymap[VK_LWIN] = "LWIN";
	keymap[VK_RWIN] = "RWIN";
	keymap[VK_APPS] = "APPS";
	keymap[VK_SLEEP] = "SLEEP";
	keymap[VK_NUMPAD0] = "NUM0";
	keymap[VK_NUMPAD1] = "NUM1";
	keymap[VK_NUMPAD2] = "NUM2";
	keymap[VK_NUMPAD3] = "NUM3";
	keymap[VK_NUMPAD4] = "NUM4";
	keymap[VK_NUMPAD5] = "NUM5";
	keymap[VK_NUMPAD6] = "NUM6";
	keymap[VK_NUMPAD7] = "NUM7";
	keymap[VK_NUMPAD8] = "NUM8";
	keymap[VK_NUMPAD9] = "NUM9";
	keymap[VK_MULTIPLY] = "*";
	keymap[VK_ADD] = "PLUS";
// 	keymap[VK_SEPARATOR] = ",";
	keymap[VK_SUBTRACT] = "-";
	keymap[VK_DECIMAL] = ".";
	keymap[VK_DIVIDE] = "/";
	keymap[VK_F1] = "F1";
	keymap[VK_F2] = "F2";
	keymap[VK_F3] = "F3";
	keymap[VK_F4] = "F4";
	keymap[VK_F5] = "F5";
	keymap[VK_F6] = "F6";
	keymap[VK_F7] = "F7";
	keymap[VK_F8] = "F8";
	keymap[VK_F9] = "F9";
	keymap[VK_F10] = "F10";
	keymap[VK_F11] = "F11";
	keymap[VK_F12] = "F12";
	keymap[VK_F13] = "F13";
	keymap[VK_F14] = "F14";
	keymap[VK_F15] = "F15";
	keymap[VK_F16] = "F16";
	keymap[VK_F17] = "F17";
	keymap[VK_F18] = "F18";
	keymap[VK_F19] = "F19";
	keymap[VK_F20] = "F20";
	keymap[VK_F21] = "F21";
	keymap[VK_F22] = "F22";
	keymap[VK_F23] = "F23";
	keymap[VK_F24] = "F24";
	keymap[VK_NUMLOCK] = "NUMLOCK";
	keymap[VK_SCROLL] = "SCROLL";
	keymap[VK_LSHIFT] = "SHIFT";
	keymap[VK_RSHIFT] = "RSHIFT";
	keymap[VK_LCONTROL] = "LCTRL";
	keymap[VK_RCONTROL] = "RCTRL";
	keymap[VK_LMENU] = "LMENU";
	keymap[VK_RMENU] = "RMENU";
	keymap[VK_BROWSER_BACK] = "BROWSER_BACK";
	keymap[VK_BROWSER_FORWARD] = "BROWSER_FORWARD";
	keymap[VK_BROWSER_REFRESH] = "BROWSER_REFRESH";
	keymap[VK_BROWSER_STOP] = "BROWSER_STOP";
	keymap[VK_BROWSER_SEARCH] = "BROWSER_SEARCH";
	keymap[VK_BROWSER_FAVORITES] = "BROWSER_FAVORITES";
	keymap[VK_BROWSER_HOME] = "BROWSER_HOME";
	keymap[VK_VOLUME_MUTE] = "VOLUME_MUTE";
	keymap[VK_VOLUME_DOWN] = "VOLUME_DOWN";
	keymap[VK_VOLUME_UP] = "VOLUME_UP";
	keymap[VK_MEDIA_NEXT_TRACK] = "MEDIA_NEXT_TRACK";
	keymap[VK_MEDIA_PREV_TRACK] = "MEDIA_PREV_TRACK";
	keymap[VK_MEDIA_STOP] = "MEDIA_STOP";
	keymap[VK_MEDIA_PLAY_PAUSE] = "MEDIA_PLAY_PAUSE";
	keymap[VK_LAUNCH_MAIL] = "LAUNCH_MAIL";
	keymap[VK_LAUNCH_MEDIA_SELECT] = "LAUNCH_MEDIA_SELECT";
	keymap[VK_LAUNCH_APP1] = "LAUNCH_APP1";
	keymap[VK_LAUNCH_APP2] = "LAUNCH_APP2";
	keymap[VK_PLAY] = "PLAY";
	keymap[VK_ZOOM] = "ZOOM";
	keymap[VK_OEM_1] = ";";
	keymap[VK_OEM_COMMA] = ",";
	keymap[VK_OEM_3] = "~";
	keymap[VK_OEM_4] = "[";
	keymap[VK_OEM_6] = "]";
	keymap[VK_OEM_5] = "\\";
	

	try
	{
		if ((key >= 0x30 && key <= 0x39) || (key >= 0x41 && key <= 0x5A))
		{
			char letter = (int)key;
			std::string humanReadableKey = std::string(1, letter);

			return humanReadableKey;
		}

		if (keymap.find(key) != keymap.end())
		{
			return keymap[key];
		} else
		{
			std::stringstream sstream;
			sstream << std::hex << key;
			std::string result = sstream.str();
			for (auto & c : result) c = toupper(c);

			return "0x" + result;
		}
	} catch (...)
	{
		return std::to_string(key);
	}
}