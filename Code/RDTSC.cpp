#include <windows.h>
#include <stdio.h>
#include <intrin.h>
#include <tchar.h>

#define SERIAL_THRESHOLD 0x10000 // 10,000h ticks

/*
RDSTC is a famous x86 instruction to count the number of cycle since reset.
This can be used to detect the VM. Thanks to Forcepoint for blog article.
*/

#define LODWORD(_qw)    ((DWORD)(_qw))
/*BOOL rdtsc_diff_locky()
{
	ULONGLONG tsc1;
	ULONGLONG tsc2;
	ULONGLONG tsc3;
	DWORD i = 0;

	// Try this 10 times in case of small fluctuations
	for (i = 0; i < 10; i++)
	{
		tsc1 = __rdtsc();

		// Waste some cycles - should be faster than CloseHandle on bare metal
		GetProcessHeap();

		tsc2 = __rdtsc();

		// Waste some cycles - slightly longer than GetProcessHeap() on bare metal
		CloseHandle(0);

		tsc3 = __rdtsc();

		// Did it take at least 10 times more CPU cycles to perform CloseHandle than it took to perform GetProcessHeap()?
		if ((LODWORD(tsc3) - LODWORD(tsc2)) / (LODWORD(tsc2) - LODWORD(tsc1)) >= 10)
			return TRUE;
	}

	// We consistently saw a small ratio of difference between GetProcessHeap and CloseHandle execution times
	// so we're probably in a VM!
	return FALSE;
}*/


/*
CPUID is an instruction which cauz a VM Exit to the VMM,
this little overhead can show the presence of a hypervisor
*/

BOOL rdtsc_diff_vmexit()
{
	ULONGLONG tsc1 = 0;
	ULONGLONG tsc2 = 0;
	ULONGLONG avg = 0;
	INT cpuInfo[4] = {};

	// Try this 10 times in case of small fluctuations
	for (INT i = 0; i < 10; i++)
	{
		tsc1 = __rdtsc();
		__cpuid(cpuInfo, 0);
		tsc2 = __rdtsc();

		// Get the delta of the two RDTSC
		avg += (tsc2 - tsc1);
	}

	// We repeated the process 10 times so we make sure our check is as much reliable as we can
	avg = avg / 10;
	return (avg < 1000 && avg > 0) ? FALSE : TRUE;
}

int main(){
	printf("rdtsc_diff_vmexit()");
	if (rdtsc_diff_vmexit())
		printf("Debugging Detected!\n");
	else
		printf("No Debugging\n");

	//printf("rdtsc_diff_locky()");
	/*if (!rdtsc_diff_locky())
		printf("Debugging Detected!\n");
	else
		printf("No Debugging\n");*/
	return 0;
}
