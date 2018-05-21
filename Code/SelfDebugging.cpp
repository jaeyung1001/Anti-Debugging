#include <Windows.h>
#include <stdio.h>

// Debug self is a function that uses CreateProcess
// to create an identical copy of the current process
// and debugs it
void DebugSelf()
{
	HANDLE hProcess = NULL;
	DEBUG_EVENT de;
	PROCESS_INFORMATION pi;
	STARTUPINFO si;
	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
	ZeroMemory(&si, sizeof(STARTUPINFO));
	ZeroMemory(&de, sizeof(DEBUG_EVENT));

	GetStartupInfo(&si);

	// Create the copy of ourself
	CreateProcess(NULL, GetCommandLine(), NULL, NULL, FALSE,
		DEBUG_PROCESS, NULL, NULL, &si, &pi);

	// Continue execution
	ContinueDebugEvent(pi.dwProcessId, pi.dwThreadId, DBG_CONTINUE);

	// Wait for an event
	WaitForDebugEvent(&de, INFINITE);
}

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