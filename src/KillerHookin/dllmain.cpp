
#include "Common/ConsoleCommands.h"
#include "Common/Globals.h"
#include "Features/AddFeatures.h"
#include "Hooking/ConsoleHooking.h"
#include "Hooking/GraphicsHooking.h"

DWORD WINAPI DLLEnter(LPVOID module);
void DLLExit();

BOOL APIENTRY DllMain(HMODULE hModule,
  DWORD  ul_reason_for_call,
  LPVOID lpReserved
)
{
  switch (ul_reason_for_call)
  {
  case DLL_PROCESS_ATTACH:
    DisableThreadLibraryCalls(hModule);
    CreateThread(NULL, 0, &DLLEnter, hModule, 0, 0);
    break;
  }
  return TRUE;
}

DWORD WINAPI DLLEnter(LPVOID module)
{
  Globals::g_module = (HMODULE)module;
  Globals::g_baseAddress = (size_t)GetModuleHandle(NULL);

#ifdef _DEBUG
  int i = 0;
  while (!IsDebuggerPresent() && i++ < 12)
    Sleep(500);
#endif

  // Creating console, need to reroute the streams.
  //if (!AllocConsole())
  //{
  //  DWORD err = GetLastError();
  //  MessageBox(NULL, "The console window could not be created", NULL, MB_ICONEXCLAMATION);
  //  goto end;
  //}
  //freopen_s((FILE**)stdin, "CONIN$", "r", stdin);
  //freopen_s((FILE**)stderr, "CONOUT$", "w", stderr);
  //freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);  
  //
  //HANDLE hConOut = CreateFile("CONOUT$", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
  //HANDLE hConIn = CreateFile("CONIN$", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
  //SetStdHandle(STD_OUTPUT_HANDLE, hConOut);
  //SetStdHandle(STD_ERROR_HANDLE, hConOut);
  //SetStdHandle(STD_INPUT_HANDLE, hConIn);
  //
  //HWND console = GetConsoleWindow();
  //ShowWindow(console, SW_SHOWDEFAULT);

  if (MH_Initialize() != MH_OK)
    goto end;

  if (!Hookin::Console::HookFunctions())
    goto end;
  if (!Hookin::Graphics::HookFunctions())
    goto end;

  Features::AddFeatures();
  Features::InitializeFeatures();

  MH_EnableHook(MH_ALL_HOOKS);

  ConsoleCommands::RegisterConsoleCommands();

  //// Test message to make sure its all working
  ConsolePrintf(ConsoleColours::RED, "Injection success, welcome to killers amazing library");

  Globals::g_running = true;
  while (Globals::g_running)
  {
    Features::UpdateFeatures(1000 / 16);
    Sleep(16);
  }

  Sleep(30);

  ConsolePrintf(ConsoleColours::RED, "So long and thanks for all the fish.");

  ConsoleCommands::UnregisterConsoleCommands();

  MH_DisableHook(MH_ALL_HOOKS);

  Features::DeinitializeFeatures();

  if (Hookin::Graphics::g_imguiInitialized)
  {
    if (Hookin::Graphics::g_imguiType == 3)
      ImGui_ImplOpenGL3_Shutdown();
    else
      ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
  }

end:
  DLLExit();
  return 0;
}

void DLLExit()
{
  Globals::g_running = false;

  //HWND console = GetConsoleWindow();
  //ShowWindow(console, SW_HIDE);
  //FreeConsole();

  MH_Uninitialize();

  FreeLibraryAndExitThread(Globals::g_module, 0);
}
