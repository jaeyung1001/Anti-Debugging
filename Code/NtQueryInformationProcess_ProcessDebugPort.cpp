#include<windows.h>
#include<stdio.h>

typedef DWORD(WINAPI *PFZWQUERYINFORMATIONPROCESS) (
	HANDLE		ProcessHandle,
	DWORD		ProcessInformationClass,	// Origianl : _PROCESS_INFORMATION_CLASS
	PVOID		ProcessInformation,
	ULONG		ProcessInformationLength,
	PULONG		ReturnLength
	);

BOOL anti_debug()
{
	BOOL result = FALSE;
	DWORD ProcessDebugPort;

	PFZWQUERYINFORMATIONPROCESS pfZwQueryInformationProcess;
	HMODULE h_ntdll = GetModuleHandle(L"ntdll.dll");
	pfZwQueryInformationProcess = (PFZWQUERYINFORMATIONPROCESS)GetProcAddress(h_ntdll, "ZwQueryInformationProcess");
	pfZwQueryInformationProcess(GetCurrentProcess(), 0x7, &ProcessDebugPort, 4, 0);	// 0x7 : ProcessDebugPort
	if (ProcessDebugPort == -1) result = TRUE;
	return result;
}

int main(int argc, char **argv)
{
	if (anti_debug())
		printf("Debugger Detected\n");
	else
		printf("No Debugger...\n");
	return 0;
}