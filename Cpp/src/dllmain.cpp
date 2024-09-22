#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "modloader.h"
#include <iostream>
#include <fstream>

DWORD WINAPI ThreadProc(LPVOID lpParam)
{
    SuspendThread(lpParam);
    System::Console::WriteLine("Hello!");
    LoadMods();
    ResumeThread(lpParam);
    return 0;
}

#pragma unmanaged
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call != DLL_PROCESS_ATTACH)
        return TRUE;

    AllocConsole();
    freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
    HANDLE thisThread = OpenThread(THREAD_ALL_ACCESS, FALSE, GetCurrentThreadId());
    HANDLE loaderThread = CreateThread(NULL, 0, ThreadProc, thisThread, 0, NULL);
    //BOOL i = SwitchToThread();
    std::cout << "Switch to Thread: " << i << std::endl;
    return TRUE;
}