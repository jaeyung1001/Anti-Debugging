#include <windows.h>
#include <excpt.h>
#include <stdio.h>

BOOL anti_debug_flag = FALSE;

EXCEPTION_DISPOSITION __cdecl _except_handler(
	__in struct _EXCEPTION_RECORD 	* _ExceptionRecord,
	__in void 					* _EstablisherFrame,
	__inout struct _CONTEXT 			* _ContextRecord,
	__inout void 					* _DispatcherContext
	)
{
	_ContextRecord->Ecx = 1;

	if (_ContextRecord->Dr0 || _ContextRecord->Dr1 || _ContextRecord->Dr2 || _ContextRecord->Dr3)
		anti_debug_flag = TRUE;
	return ExceptionContinueExecution;
}

void anti_debug()
{
	ULONG seh_handler = (ULONG)_except_handler;

	__asm
	{
		push	seh_handler
			push	fs : [0]
			mov		fs : [0], esp				// SEH Chain Install

			mov		eax, 1
			xor		ecx, ecx
			div		ecx					// Exception Divide by Zero

			mov		eax, dword ptr[esp]
			mov		fs : [0], eax
			add		esp, 8
	}
}

int main(int argc, char **argv)
{
	anti_debug();

	if (anti_debug_flag)
		printf("Debugger Detected\n");
	else
		printf("No Debugger...\n");
	return 0;
}