#include <windows.h>
#include <stdio.h>

BOOL anti_debug()
{
	BOOL result = FALSE;
	HKEY hKey;
	char lpData[256];
	DWORD lpSize = sizeof(lpData);

	RegOpenKeyEx(HKEY_LOCAL_MACHINE,
		L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\AeDebug",
		0, KEY_QUERY_VALUE, &hKey);
	RegQueryValueEx(hKey, L"Debugger", NULL, NULL, (LPBYTE)&lpData, &lpSize);
	strlwr(lpData);

	if (strstr(lpData, "ollydbg") || strstr(lpData, "windbg") ||
		strstr(lpData, "ImmunityDebugger") || strstr(lpData, "ida"))
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