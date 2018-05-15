#include<iostream>
#include <Windows.h>
using namespace std;

int CheckTEB();


int main(int argc, char* argv[])
{
	if (CheckTEB())
		MessageBoxA(NULL, "Debugger Detected", "", MB_OK);
	return 0;
}

int CheckTEB()
{
	int debugger_flag = 0;
	int a;
	__asm
	{
		mov eax, fs:[30h]
			push ecx
			mov ecx, [eax + 2]
			mov a, ecx
			pop ecx

	}
	return a;
}