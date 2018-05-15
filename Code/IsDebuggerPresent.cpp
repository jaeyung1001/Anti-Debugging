#define _WIN32_WINNT 0x0501

#include <windows.h>

#include <stdio.h>

BOOL anti_debug()
{
	return IsDebuggerPresent();
}

int main(int argc, char **argv)
{
	if (anti_debug())
		printf("Debugger Detected\n");
	else
		printf("No Debugger...\n");
	return 0;
}