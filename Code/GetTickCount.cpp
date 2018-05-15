#include <windows.h>
#include <stdio.h>
#pragma comment(lib, "winmm.lib")
BOOL anti_debug(DWORD count1)
{
	DWORD count2;
	count2 = GetTickCount();
	if ((count2 - count1) > 0x10) {
		return 1;
	}
	return 0;
}

int main(int argc, char **argv)
{
	DWORD count1;
	count1 = GetTickCount();
	if (anti_debug(count1))
		printf("Debugger Detected\n");
	else
		printf("No Debugger...\n");
	return 0;
}