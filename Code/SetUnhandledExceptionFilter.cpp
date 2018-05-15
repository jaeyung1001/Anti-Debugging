#include <windows.h>
#include <excpt.h>
#include <stdio.h>
LONG WINAPI UnhandledExcepFilter(PEXCEPTION_POINTERS pExcepPointers) {
	SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER) pExcepPointers->ContextRecord->Eax);
	pExcepPointers->ContextRecord->Eip += 2;
	return EXCEPTION_CONTINUE_EXECUTION;
}

int main(int argc, char **argv) {
	SetUnhandledExceptionFilter(UnhandledExcepFilter);
	__asm{
		xor eax, eax
	}
	__asm{
		div eax
	}
	printf("No Debugger...\n");
	return 0;
}
