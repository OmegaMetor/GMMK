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

    LPCWSTR original_lpFileName = lpFileName;

    if(path.filename().wstring() == L"data.win")
    {
        if(!patched_data_path)
        {
            std::cout << "data.win not yet loaded, calling patcher." << std::endl;
    
            patched_data_path = L"testdata.win";
        }
        std::wcout << "Opening data.win from " << patched_data_path << std::endl;
        lpFileName = patched_data_path;
    }

    HANDLE fileHandle = original_CreateFileW(
        lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes,
        dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);

    if (fileHandle != INVALID_HANDLE_VALUE)
        return fileHandle;
    
    // Modified data.win does not exist here, time to open the launcher.

    // Check locally for launcher install (in horizon folder)

    std::string horizon_path;
    
    DWORD horizonFolderAttributes = GetFileAttributes("horizon-gm");
    
    

    if (horizonFolderAttributes != INVALID_FILE_ATTRIBUTES) {
        horizon_path = "horizon-gm/Horizon_Launcher.exe";
    } else {
        // TODO: Get Horizon path from registry (or somewhere else)
    }

    if (!horizon_path.empty()) {
        // TODO: Launch Horizon using horizon_path.
        exit(0);
    }

    // TODO: Show warning message, ask about deleting.

    return original_CreateFileW(
        original_lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes,
        dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
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

    if (should_modify)
    {
        if(!setup_hooks()) has_errored = true;
    }

    return TRUE;
}