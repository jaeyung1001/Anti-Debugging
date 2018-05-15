#include <windows.h>
#include <stdio.h>

BOOL anti_debug()
{
	int result = 0;
	void *pHeap;
	DWORD Flags, ForceFlags;

	__asm
	{
		mov eax, large fs : 30h // PEB saved to EAX
		mov eax, dword ptr[eax + 18h] // ProcessHeap(offset 0x18 relative to PEB) saved to EAX
		cmp dword ptr ds : [eax + 10h], 0 // Check whether ForceFlags field(offset 0x10 relative to ProcessHeap) is 0
		jne DebuggerDetected // If previous test returned non zero, debugger is present

	DebuggerDetected:
		mov result, 1;
	}

	if (result)
		result = 1;
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