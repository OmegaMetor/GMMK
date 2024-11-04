#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#pragma managed
LPCWSTR _patch(LPCWSTR data_win_path) {
    System::Console::WriteLine("Hello!");
    return L"testdata.win";
}

#pragma unmanaged
__declspec(dllexport) LPCWSTR patch(LPCWSTR data_win_path) {
    return _patch(data_win_path);
};

