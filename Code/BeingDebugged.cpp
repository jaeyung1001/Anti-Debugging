#include <windows.h>
#include <stdio.h>

DWORD anti_debug()
{
	__asm
	{
		mov eax, fs:[0x30]				// PEB 접근
			movzx eax, byte ptr[eax + 2]		// PEB.BeingDebugged 멤버 접근
	}
}

int main(int argc, char **argv)
{
	if (anti_debug())
		printf("Debugger Detected\n");
	else
		printf("No Debugger...\n");
	return 0;
}