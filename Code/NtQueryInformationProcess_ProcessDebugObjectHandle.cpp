
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
	DWORD fRet;
	DWORD ProcessDebugObejctHandle;

	PFZWQUERYINFORMATIONPROCESS pfZwQueryInformationProcess;
	HMODULE h_ntdll = GetModuleHandle(L"ntdll.dll");
	pfZwQueryInformationProcess = (PFZWQUERYINFORMATIONPROCESS)GetProcAddress(h_ntdll, "ZwQueryInformationProcess");
	fRet = pfZwQueryInformationProcess(GetCurrentProcess(), 0x1e, &ProcessDebugObejctHandle, 4, 0);	// 0x1e : ProcessObjectHandle
	if (ProcessDebugObejctHandle) result = TRUE;	// 3번째 인자 전달 값 확인
	if (fRet == 0) result = TRUE;				// 반환 값 확인
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