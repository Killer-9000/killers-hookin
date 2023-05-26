#pragma once

#include "Globals.h"
#include "Hooking/ConsoleHooking.h"

namespace ConsoleCommands
{
	bool CMD_TestFunc(char* name, char* args)
	{
		ConsolePrintf(ConsoleColours::WHITE, "test_func has been called.");
		return true;
	}

	bool CMD_HookingQuit(char* name, char* args)
	{
		Globals::g_running = false;
		return true;
	}

	void RegisterConsoleCommands()
	{
		RegisterConsoleCommand("test_func", &CMD_TestFunc, ConsoleCategories::GM, "Test description");
		RegisterConsoleCommand("hooking_quit", &CMD_HookingQuit, ConsoleCategories::GM, "Quit the hooking library.");
	}
	void UnregisterConsoleCommands()
	{
		UnregisterConsoleCommand("hooking_quit");
		UnregisterConsoleCommand("test_func");
	}
}