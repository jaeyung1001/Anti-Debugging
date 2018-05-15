#include<windows.h>
#include<stdio.h>

typedef DWORD(WINAPI *PFZWSETINFORMATIONTHREAD) (
	HANDLE		ThreadHandle,
	DWORD		ThreadInformationClass,		// Original : _THREAD_INFORMATION_CLASS
	PVOID		ThreadInformation,
	ULONG		ThreadInformationLength
	);

void anti_debug()
{
	PFZWSETINFORMATIONTHREAD pfZwSetInformationThread;
	HMODULE h_ntdll = GetModuleHandle(L"ntdll.dll");
	pfZwSetInformationThread = (PFZWSETINFORMATIONTHREAD)GetProcAddress(h_ntdll, "ZwSetInformationThread");
	pfZwSetInformationThread(GetCurrentThread(), 0x11, 0, 0);	// 0x11 : ThreadHideFromDebugger
	printf("Debugger Dettached\n");
}

int main(int argc, char **argv)
{
	anti_debug();
	return 0;
}