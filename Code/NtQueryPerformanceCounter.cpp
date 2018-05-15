#include <windows.h>
#include <stdio.h>

BOOL anti_debug(LARGE_INTEGER cnt1)
{
	LARGE_INTEGER cnt2;
	QueryPerformanceCounter(&cnt2);
	if ((cnt2.QuadPart - cnt1.QuadPart) > 0xFF) {
		return 1;
	}
	return 0;
}

int main(int argc, char **argv)
{
	LARGE_INTEGER cnt1;
	QueryPerformanceCounter(&cnt1);
	if (anti_debug(cnt1))
		printf("Debugger Detected\n");
	else
		printf("No Debugger...\n");
	return 0;
}