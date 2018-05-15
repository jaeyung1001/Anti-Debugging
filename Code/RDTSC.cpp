#include <windows.h>
#include <stdio.h>
#include <intrin.h>
BOOL anti_debug(unsigned __int64 cnt1)
{
	unsigned __int64 cnt2;
	cnt2 = __rdtsc();
	if ((cnt2 - cnt1) > 0xFF) {
		return 1;
	}
	return 0;
}

int main(int argc, char **argv)
{
	unsigned __int64 cnt1;
	cnt1 = __rdtsc();
	if (anti_debug(cnt1))
		printf("Debugger Detected\n");
	else
		printf("No Debugger...\n");
	return 0;
}