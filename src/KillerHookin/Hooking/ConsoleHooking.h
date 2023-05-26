#pragma once

#include "CommonHooking.h"

namespace Hookin::Console
{
	namespace ConsoleWrite
	{
		typedef void (*Func)(const char*, int);
		static Func OriginalFunc;
	}

	namespace ConsoleCommandRegister
	{
		//                Command name, Argument list
		typedef bool (*Callback)(char*, char*);
		typedef void (*Func)(const char*, Callback, int, const char*);
		static Func OriginalFunc;
	}

	namespace ConsoleCommandUnregister
	{
		typedef void (*Func)(const char*);
		static Func OriginalFunc;
	}

	bool HookFunctions()
	{
			ConsoleWrite::OriginalFunc = (ConsoleWrite::Func)0x00765270;
			ConsoleCommandRegister::OriginalFunc = (ConsoleCommandRegister::Func)0x00769100;
			ConsoleCommandUnregister::OriginalFunc = (ConsoleCommandUnregister::Func)0x007689e0;

			// ConsoleCommandInvalidPtrCheck, disregards anything out of exe.
			WriteProtectedMemory((LPVOID)0x0086b5a0, 0xc3, 1);

			return true;
	}
}

enum ConsoleCategories
{
	DEBUG = 1,
	CONSOLE,
	GRAPHICS,
	GAME,
	DEFAULT,
	NET,
	SOUND,
	GM
};
enum ConsoleColours
{
	WHITE = 1,
	GREY = 2,
	RED = 3,
	YELLOW = 4,
	LIGHT_GREY = 7,
	BLACK = 8,
	SEE_THROUGH = 11
};
void ConsolePrintf(ConsoleColours colour, const char* msg, ...)
{
	char message[512] = { 0 };
	va_list args;
	va_start(args, msg);
	vsnprintf(message, 512, msg, args);
	va_end(args);
	Hookin::Console::ConsoleWrite::OriginalFunc(message, (int)colour);
}
void ConsolePrintf(const char* msg, ...)
{
	char message[512] = { 0 };
	va_list args;
	va_start(args, msg);
	vsnprintf(message, 512, msg, args);
	va_end(args);
	ConsolePrintf(ConsoleColours::WHITE, message);
}
void RegisterConsoleCommand(const char* name, Hookin::Console::ConsoleCommandRegister::Callback callback, ConsoleCategories category, const char* desc)
{
	Hookin::Console::ConsoleCommandRegister::OriginalFunc(name, callback, (int)category, desc);
}
void UnregisterConsoleCommand(const char* name)
{
	Hookin::Console::ConsoleCommandUnregister::OriginalFunc(name);
}