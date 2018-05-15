#include <windows.h>
#include <stdio.h>

BOOL anti_debug(SYSTEMTIME s_time1, FILETIME f_time1)
{
	SYSTEMTIME s_time2;
	FILETIME f_time2;
	GetSystemTime(&s_time2);
	SystemTimeToFileTime(&s_time2, &f_time2);
	if ((f_time2.dwLowDateTime - f_time1.dwLowDateTime) / 10000 > 1000) {
		return 1;
	}
	return 0;
}

int main(int argc, char **argv)
{
	SYSTEMTIME s_time1;
	FILETIME f_time1;
	GetSystemTime(&s_time1);
	SystemTimeToFileTime(&s_time1, &f_time1);
	if (anti_debug(s_time1, f_time1))
		printf("Debugger Detected\n");
	else
		printf("No Debugger...\n");
	return 0;
}