#pragma once

#include <MinHook.h>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

namespace Hookin
{
	template <typename TYPE>
	void WriteProtectedMemory(void* dst, const TYPE value, size_t size = sizeof(TYPE))
	{
		DWORD oldProc = 0;
		VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldProc);
		memcpy(dst, &value, size);
		VirtualProtect(dst, size, oldProc, &oldProc);
	}
	template <typename TYPE>
	void WriteProtectedMemory(void* dst, const TYPE* value, size_t size = sizeof(TYPE))
	{
		DWORD oldProc = 0;
		VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldProc);
		memcpy(dst, value, size);
		VirtualProtect(dst, size, oldProc, &oldProc);
	}
}

#define HOOK_FUNC(OFFSET, NAME) \
		if (MH_CreateHook((LPVOID)OFFSET, &NAME::Hook, (LPVOID*)&NAME::Original) != MH_OK) \
			ConsolePrintf("Failed to hook '%s'\n", #NAME);

#define HOOK_FUNC2(NAME) HOOK_FUNC(NAME::Address, NAME)

#define HOOK_VTABLE(OFFSET, NAME) \
		NAME::Original = (NAME::Func)(OFFSET); \
		WriteProtectedMemory((void*)OFFSET, (uint32_t)&NAME::Hook);