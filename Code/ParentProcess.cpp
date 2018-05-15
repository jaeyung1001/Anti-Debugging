#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>
#include <psapi.h>

#pragma comment(lib, "psapi.lib")

int GetProcssName(DWORD PID, char *buff, int size)
{
    int len = 0;
    HANDLE hProc = NULL;

    if ( (hProc = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, PID)) != NULL)
    {
        len = GetModuleBaseName(hProc, NULL, (LPWSTR)buff, size);
        CloseHandle (hProc);
    }

    return len;
}

bool anti_debug()
{
    int pid = -1, len;
    HANDLE h = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 pe = { 0 };
    char name[100];
	pe.dwSize = sizeof(PROCESSENTRY32);
	pid = GetCurrentProcessId();
  
    if( Process32First(h, &pe)) {
    	do {
    		if (pe.th32ProcessID == pid) {
    			break;
    		}
    	} while( Process32Next(h, &pe));
    }
    CloseHandle(h);
	len = GetProcssName(pe.th32ParentProcessID, name, sizeof(name)-1);
	name[len]=0;
	if(!memcmp(name, "OllyDbg",4)){
		return 1;
	}
	return 0;
}

int main(int argc, char **argv)
{
	if(anti_debug())
		printf("Debugger Detected\n");
	else
		printf("No Debugger...\n");
	return 0;
}