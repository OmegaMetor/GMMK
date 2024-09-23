#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <unordered_set>
#include <minhook.h>

bool has_errored = false;

std::unordered_set<HANDLE> data_win_handles;

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
    HANDLE hTemplateFile, bool hi )
{
    HANDLE fileHandle = original_CreateFileW(
        lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes,
        dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);

    std::filesystem::path path(lpFileName);

    if(path.filename().wstring() == L"data.win")
    {
        std::cout << "Captured data.win handle: " << fileHandle << std::endl;
        data_win_handles.insert(fileHandle);

    }

    return fileHandle;
}

typedef BOOL (WINAPI* ReadFileFunc)(
    HANDLE hFile,
    LPVOID lpBuffer,
    DWORD nNumberOfBytesToRead,
    LPDWORD lpNumberOfBytesRead,
    LPOVERLAPPED lpOverlapped
);

ReadFileFunc original_ReadFile = NULL;

BOOL WINAPI hook_ReadFile(
    HANDLE hFile,
    LPVOID lpBuffer,
    DWORD nNumberOfBytesToRead,
    LPDWORD lpNumberOfBytesRead,
    LPOVERLAPPED lpOverlapped)
{
    if(data_win_handles.contains(hFile))
        std::cout << "Hooked ReadFile: " << nNumberOfBytesToRead << " bytes from data.win handle " << hFile << std::endl;

    // TODO: If reading the data.win, instead redirect to wherever the modified data.win is.
    // Maybe, disable hook, call c# function (in other c++/cli dll, to avoid having to do the dotnet runtime stuff or mono)
    // c# function returns a path (as a string), CreateFileW that handle (also disable createfilew hook?)
    // Then, here, instead of reading from the requested handle, read from our data.win handle.

    // Alternatively, have the c# function return a byte array,
    // and instead of reading from a separate handle,
    // simply reimplement ReadFile from an array of bytes.
    // Probably not very simple though.

    return original_ReadFile(
        hFile, lpBuffer, nNumberOfBytesToRead, lpNumberOfBytesRead, lpOverlapped);
}

typedef BOOL (*CloseHandleFunc)(
    HANDLE handle
);

CloseHandleFunc original_CloseHandle = NULL;

BOOL hook_CloseHandle(HANDLE handle)
{
    if(data_win_handles.contains(handle))
    {
        std::cout << "Removing data.win handle " << handle << std::endl;
        data_win_handles.erase(handle);

    }
    return original_CloseHandle(handle);
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

    std::wcout << "Creating ReadFile hook" << std::endl;
    
    if(MH_CreateHook(&ReadFile, &hook_ReadFile, reinterpret_cast<LPVOID*>(&original_ReadFile)) != MH_OK){
        std::cout << "Failed to create ReadFile hook!" << std::endl;
        return false;
    }

    if(MH_EnableHook(&ReadFile) != MH_OK) {
        std::cout << "Failed to enable ReadFile hook!" << std::endl;
        return false;
    }

    std::cout << "Creating CloseHandle hook" << std::endl;

    if(MH_CreateHook(&CloseHandle, &hook_CloseHandle, reinterpret_cast<LPVOID*>(&original_CloseHandle)) != MH_OK){
        std::cout << "Failed to create CloseHandle hook!" << std::endl;
        return false;
    }

    if(MH_EnableHook(&CloseHandle) != MH_OK) {
        std::cout << "Failed to enable CloseHandle hook!" << std::endl;
        return false;
    }

    return true;
}

#pragma unmanaged
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call != DLL_PROCESS_ATTACH)
        return TRUE;

    AllocConsole();
    freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);

    bool has_errored = false;

    if(!setup_hooks()) has_errored = true;

    return TRUE;
}