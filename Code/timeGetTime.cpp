#include <windows.h>
#include <stdio.h>
#pragma comment(lib, "winmm.lib")
BOOL anti_debug(DWORD time1)
{
	DWORD time2;
	time2 = timeGetTime();

	if ((time2 - time1) > 0x10) {
		return 1;
	}
	return 0;
}

int main(int argc, char **argv)
{
	DWORD time1;
	time1 = timeGetTime();
	if (anti_debug(time1))
		printf("Debugger Detected\n");
	else
		printf("No Debugger...\n");
	return 0;
}