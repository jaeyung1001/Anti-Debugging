#include <Windows.h>
#include <stdio.h>

LONG WINAPI UnhandledExcepFilter(PEXCEPTION_POINTERS pExcepPointers)
{
	// Restore old UnhandledExceptionFilter
	SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)
		pExcepPointers->ContextRecord->Eax);

	// Skip the exception code
	pExcepPointers->ContextRecord->Eip += 2;

	return EXCEPTION_CONTINUE_EXECUTION;
}

int main()
{
	SetUnhandledExceptionFilter(UnhandledExcepFilter);
	__asm{xor eax, eax}
	__asm{div eax}
	printf("No Debugging!\n");
	// Execution resumes here if there is no debugger
	// or if there is a debugger it will never
	// reach this point of execution
}