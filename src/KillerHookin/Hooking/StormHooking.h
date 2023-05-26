#pragma once

#include "CommonHooking.h"

namespace Hookin::Storm
{
	namespace SFileCloseFile
	{
		typedef int (*Func)(HANDLE);
		static Func OriginalFunc;
	}
	namespace SFileCreateFile
	{
		typedef int (*Func)(HANDLE, const char*, uint32_t, uint32_t, HANDLE*);
		static Func OriginalFunc;
	}
	namespace SFileGetFileSize
	{
		typedef void (*Func)(HANDLE, void*);
		static Func OriginalFunc;
	}
	namespace SFileOpenFile
	{
		typedef void (*Func)(const char*, HANDLE*);
		static Func OriginalFunc;
	}
	namespace SFileReadFile
	{
		typedef void (*Func)(HANDLE, uint8_t*, uint32_t, void*, void*);
		static Func OriginalFunc;
	}

	bool HookFunctions(size_t base)
	{
#define GET_ADDR(ADDR) ((LPVOID)ADDR)

		SFileCloseFile::OriginalFunc = (SFileCloseFile::Func)GET_ADDR(0x00422910);
		SFileCreateFile::OriginalFunc = (SFileCreateFile::Func)GET_ADDR(0x00460010);
		SFileGetFileSize::OriginalFunc = (SFileGetFileSize::Func)GET_ADDR(0x004218c0);
		SFileOpenFile::OriginalFunc = (SFileOpenFile::Func)GET_ADDR(0x00424f80);
		SFileReadFile::OriginalFunc = (SFileReadFile::Func)GET_ADDR(0x00422530);

#undef GET_ADDR
		return true;
	}
}

