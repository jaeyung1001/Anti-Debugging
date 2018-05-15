#include <windows.h>
#include <stdio.h>

BOOL anti_debug()
{
	BOOL result = FALSE;

	CONTEXT ct;
	ct.ContextFlags = CONTEXT_DEBUG_REGISTERS;

	GetThreadContext(GetCurrentThread(), &ct);

	if (ct.Dr0 || ct.Dr1 || ct.Dr2 || ct.Dr3)
		result = TRUE;
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