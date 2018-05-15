#include <windows.h>
#include <stdio.h>

DWORD anti_debug()
{
	__asm
	{
		mov eax, fs:[0x30]
		movzx eax, dword ptr [eax+0x68]
	}
}

int main(int argc, char **argv)
{
	if(anti_debug())
		printf("Debugger Detected\n");
	else
		printf("No Debugger...\n");
	return 0;
}