#include <windows.h>
#include <stdio.h>

void magicnumber_ldr()
{
	void *pLdr;
	DWORD data, *base;

	__asm
	{
		mov eax, fs:[0x30]				// PEB Address
			mov eax, dword ptr[eax + 0xc]	// LDR Address
			mov pLdr, eax;
	}

	base = (DWORD *)pLdr;

	while (1) {
		data = *base++;
		if (data == 0xfeeefeee)	break;
	}
}

void magicnumber_heap()
{
	void *pHeap;
	DWORD data, *base;

	__asm
	{
		mov eax, fs:[0x30]				// PEB Address
			mov eax, dword ptr[eax + 0x18]	// HEAP Address
			mov pHeap, eax;
	}

	base = (DWORD *)pHeap;

	while (1) {
		data = *base++;
		if (data == 0xfeeefeee)	break;
	}
}

BOOL anti_debug()
{
	BOOL result = TRUE;

	__try
	{
		magicnumber_heap();
		magicnumber_ldr();
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		result = FALSE;
	}
	return result;
}

int main(int argc, char **argv)
{
	if (anti_debug())	printf("Debugger Detected\n");
	else				printf("No Debugger...\n");
	return 0;
}