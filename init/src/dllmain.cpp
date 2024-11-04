#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <unordered_map>
#include <minhook.h>
#include <shellapi.h>

bool has_errored = false;
LPCWSTR patched_data_path = NULL;

__declspec(dllimport) LPCWSTR patch(LPCWSTR data_win_path);

typedef HANDLE (WINAPI* CreateFileWFunc)(
    LPCWSTR lpFileName,
    DWORD dwDesiredAccess,
    DWORD dwShareMode,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    DWORD dwCreationDisposition,
    DWORD dwFlagsAndAttributes,
    HANDLE hTemplateFile
);

CreateFileWFunc original_CreateFileW = NULL;

HANDLE WINAPI hook_CreateFileW(
    LPCWSTR lpFileName,
    DWORD dwDesiredAccess,
    DWORD dwShareMode,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    DWORD dwCreationDisposition,
    DWORD dwFlagsAndAttributes,
    HANDLE hTemplateFile)
{
    std::filesystem::path path(lpFileName);

    if(path.filename().wstring() == L"data.win")
    {
        if(!patched_data_path)
        {
            std::cout << "data.win not yet loaded, calling patcher." << std::endl;
    
            patched_data_path = patch(lpFileName); // TODO: Replace with c++/cli library call. `LPWSTR patch(LPWSTR data_win_path)`.
        }
        std::wcout << "Opening data.win from " << patched_data_path << std::endl;
        lpFileName = patched_data_path;
    }

    HANDLE fileHandle = original_CreateFileW(
        lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes,
        dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
    return fileHandle;

}

bool setup_hooks()
{
    if(MH_Initialize() != MH_OK) {
        std::cout << "There was a problem initializing MinHook, not loading mods." << std::endl;
        return false;
    }

    std::wcout << "Creating CreateFileW hook" << std::endl;

    if(MH_CreateHook(&CreateFileW, &hook_CreateFileW, reinterpret_cast<LPVOID*>(&original_CreateFileW)) != MH_OK){
        std::cout << "Failed to create CreateFileW hook!" << std::endl;
        return false;
    }

    if(MH_EnableHook(&CreateFileW) != MH_OK) {
        std::cout << "Failed to enable CreateFileW hook!" << std::endl;
        return false;
    }

    return true;
}

#pragma unmanaged
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call != DLL_PROCESS_ATTACH)
        return TRUE;

    // TODO: Check config for console enable
    AllocConsole();
    freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);

    bool should_modify = true;

    int num_args = 0;
    LPWSTR* args = CommandLineToArgvW(GetCommandLineW(), &num_args);

    for (int i = 0; i < num_args; i++)
    {
        if(lstrcmpW(args[i], L"-game") == 0)
        {
            should_modify = false;
        }
    }

    bool has_errored = false;
    std::cout << should_modify << std::endl;
    if (should_modify)
    {
        if(!setup_hooks()) has_errored = true;
    }

    return TRUE;
}