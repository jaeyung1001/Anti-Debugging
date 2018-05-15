#include <windows.h>
#include <stdio.h>

BOOL anti_debug()
{
	DWORD Val = 123;
	SetLastError(Val);
	OutputDebugString(L"random");
	if (GetLastError() == Val) {
		return 1;
	}
	else {
		return 0;
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