/*
Thanks to https://github.com/Archie-osu/
This is directly taken (by their suggestion) from their Uniprox repo.
*/

#include <Windows.h>

extern "C"
{
	// huge dll proxying code ahead (except it doesn't proxy shit)
	// https://learn.microsoft.com/en-us/windows/win32/api/minidumpapiset/nf-minidumpapiset-minidumpreaddumpstream
	__declspec(dllexport) BOOL MiniDumpReadDumpStream(
		PVOID BaseOfDump,
		ULONG StreamNumber,
		void* Dir,
		void* StreamPointer,
		void* StreamSize
	)
	{
		return FALSE;
	}

	// https://learn.microsoft.com/en-us/windows/win32/api/minidumpapiset/nf-minidumpapiset-minidumpwritedump
	__declspec(dllexport) BOOL MiniDumpWriteDump(
		HANDLE hProcess, 
		DWORD ProcessId, 
		HANDLE hFile,
		DWORD Type, 
		void* ExceptionParam,
		void* UserStreamParam, 
		void* CallbackParam
	)
	{
		return FALSE;
	}
}