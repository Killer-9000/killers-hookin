#pragma once

#include "CommonHooking.h"
#include "ConsoleHooking.h"

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_dx9.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "imgui/backends/imgui_impl_win32.h"

#include <d3d9.h>

#include <map>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace Hookin::Graphics
{
	void ImGui_FinishHook(void* pThis, int type);
	void RenderImGui();


	// CGxDevice*_Finish hooks.
	namespace CGxDeviceD3d9_Finish
	{
		typedef void(__fastcall* Func)(void*);
		static Func Original;
		static LPVOID Address = (LPVOID)0x006a3450;
		void __fastcall Hook(void* pThis)
		{
			ImGui_FinishHook(pThis, 1);
			Original(pThis);
		}
	}
	namespace CGxDeviceD3d9Ex_Finish
	{
		typedef void(__fastcall* Func)(void*);
		static Func Original;
		static LPVOID Address = (LPVOID)0x006a7610;
		void __fastcall Hook(void* pThis)
		{
			ImGui_FinishHook(pThis, 2);
			Original(pThis);
		}
	}
	namespace CGxDeviceOpenGl_Finish
	{
		typedef void(__fastcall* Func)(void*);
		static Func Original;
		static LPVOID Address = (LPVOID)0x0069e220;
		void __fastcall Hook(void* pThis)
		{
			ImGui_FinishHook(pThis, 3);
			Original(pThis);
		}
	}

	// Window procedure handler hook.
	static WNDPROC WndProcHandlerOriginal = nullptr;
	LRESULT __cdecl WndProcHandlerHook(HWND window, UINT msg, WPARAM wParam, LPARAM lParam);

	// EndScene hook data.
	static IDirect3DDevice9* g_device = nullptr;
	static HWND g_window = nullptr;
	static bool g_menuShown = false;
	static bool g_imguiInitialized = false;
	static int  g_imguiType = -1;

	bool HookFunctions()
	{
		HOOK_FUNC2(CGxDeviceD3d9_Finish);
		HOOK_FUNC2(CGxDeviceD3d9Ex_Finish);
		HOOK_FUNC2(CGxDeviceOpenGl_Finish);
		return true;

	}
	void ImGui_FinishHook(void* pThis, int type)
	{
		if (!g_imguiInitialized || g_imguiType != type)
		{
			if (!pThis)
				return;

			if (g_imguiType == -1)
			{
				// Setup Dear ImGui context
				IMGUI_CHECKVERSION();
				ImGui::CreateContext();
				ImGuiIO& io = ImGui::GetIO(); (void)io;
				io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;   // Enable Docking
				//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport / Platform Windows

				// Setup Dear ImGui style
				ImGui::StyleColorsDark();
			}

			g_device = *(IDirect3DDevice9**)((uint8_t*)pThis + 14716);
			g_window = *(HWND*)((uint8_t*)pThis + 14696);

			if (!ImGui_ImplWin32_Init(g_window))
				return;

			if (type == 3)
			{
				if (!ImGui_ImplOpenGL3_Init())
					return;
			}
			else
			{
				if (!ImGui_ImplDX9_Init(g_device))
					return;
			}

			WndProcHandlerOriginal = (WNDPROC)SetWindowLongPtr(g_window, GWLP_WNDPROC, (LONG_PTR)WndProcHandlerHook);


			g_imguiType = type;
			g_imguiInitialized = true;

			ConsolePrintf("[DBG] Initialized ImGui.\n");
		}

		ImGui_ImplWin32_NewFrame();
		if (type == 3)
			ImGui_ImplOpenGL3_NewFrame();
		else
			ImGui_ImplDX9_NewFrame();

		ImGui::NewFrame();
		RenderImGui();
		ImGui::EndFrame();
		ImGui::Render();

		if (type == 3)
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		else
			ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
	}

	LRESULT __cdecl WndProcHandlerHook(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		//ConsolePrintf("[DBG] WndProcHandlerHook event occured. Event: (0x%x), wParam: (0x%llx), lParam: (0x%llx).\n", msg, wParam, lParam);

		if (uMsg == WM_KEYDOWN && wParam == VK_DELETE)
		{
			g_menuShown = !g_menuShown;
			ImGui::GetIO().MouseDrawCursor = false;
		}

		if (g_menuShown)
			if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
				return 1;

		return WndProcHandlerOriginal(hWnd, uMsg, wParam, lParam);
	}

	void RenderImGui()
	{
		if (g_menuShown)
		{
			if (ImGui::Begin("Test"));
			{

			}
			ImGui::End();
		}
	}
}
