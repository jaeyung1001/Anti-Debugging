#include <windows.h>
#include <excpt.h>
#include <stdio.h>
BOOL anti_debug_flag = TRUE;
void anti_debug()
{
	__try
	{
		__asm
		{
			pushfd
				or dword ptr ss : [esp + 1], 1	// or dword ptr ss:[esp], 0x100
				popfd
				nop
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		anti_debug_flag = FALSE;
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