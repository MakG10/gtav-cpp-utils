/*
		THIS FILE IS A PART OF GTA V SCRIPT HOOK SDK
					http://dev-c.com
				(C) Alexander Blade 2015
*/

#pragma once

#include <windows.h>
#include <string>
#include <vector>

// parameters are the same as with aru's ScriptHook for IV
void OnKeyboardMessage(DWORD key, WORD repeats, BYTE scanCode, BOOL isExtended, BOOL isWithAlt, BOOL wasDownBefore, BOOL isUpNow);

bool IsKeyDown(DWORD key);
bool IsKeyJustUp(DWORD key, bool exclusive = true);
void ResetKeyState(DWORD key);

int FetchKey();
int FetchKeyUp();

bool IsKeyCombinationDown(std::string humanReadableKey);
void PressKeyCombination(std::vector<int> keys);
void PressKeyCombination(std::vector<std::string> humanReadableKeys);
void PressKey(std::string humanReadableKey);

std::vector<std::string> SplitKeyCombination(std::string humanReadableKey);
DWORD str2key(std::string humanReadableKey);
std::string key2str(DWORD key);