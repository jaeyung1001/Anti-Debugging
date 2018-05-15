#include <windows.h>
#include <stdio.h>
#include <psapi.h>
#pragma comment(lib, "psapi.lib")

BOOL anti_debug()
{
	DWORD All_process[1024], cb, process_cnt, value;
	int read;
	unsigned int i;
	HMODULE hMod = NULL;
	HANDLE hProcess;

	EnumProcesses(All_process, sizeof(All_process), &cb);
	process_cnt = cb / sizeof(DWORD);
	for (i = 0; i < process_cnt; i++){
		hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, All_process[i]);
		if (hProcess != NULL) {
			value = 0;
			if (ReadProcessMemory(hProcess, (LPCVOID)0x4B064B, &value, (SIZE_T)4, (SIZE_T *)&read)) {
				if (value == 0x594C4C4F) {
					return 1;
				}
			}
		}
	}
	return 0;
}
int main(int argc, char **argv)
{
	if (anti_debug())
		printf("Debugger Detected\n");
	else
		printf("No Debugger...\n");
	system("pause");
	return 0;
}