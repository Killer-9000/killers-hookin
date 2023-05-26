#pragma once

#include "CommonHooking.h"

namespace Hookin::Packet
{
	namespace ClientServices_SetPacketHandler
	{
		typedef void (*PacketHandler)(uint16_t opcode, );
		typedef void (*Func)(uint16_t opcode, PacketHandler handler, bool unknown);
		static Func Original;
		static LPVOID Address = (LPVOID)0x0069e220;
		void __fastcall Hook(uint16_t opcode, PacketHandler handler, bool unknown)
		{

		}
	}

	bool HookFunctions(size_t base)
	{
		HOOK_FUNC2(ClientServices_SetPacketHandler);

		return true;
	}
}

