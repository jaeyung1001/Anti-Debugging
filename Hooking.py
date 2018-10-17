from pydbg import *
from pydbg.defines import *
from utils import hooking
import sys, os
import threading
from multiprocessing import Process
# import sys, utils

dbg = pydbg()

target_name = sys.argv[1].strip("\n")
target_pid = 0
isProcess = False

# def start_target_program():
# 	os.system("ob_Hook_target.exe")

def pass_anti_analysis(dbg, args):
	print("Now hooking anti analysis method...")
	args_data = dbg.read_process_memory(args[1], args[2])
	print(args_data)
	return DBG_CONTINUE

while(True):
	for (pid, name) in dbg.enumerate_processes():
		# print(pid, name)
		if(name == target_name):
			print("Found Target Program!!!")
			target_pid = pid
			print("Set target name:{}, target pid:{}".format(target_name, target_pid))
			isProcess = True
			hooks = hooking.hook_container()
			dbg.attach(target_pid)
			'''
			HWND WINAPI FindWindow(
				_In_opt_	LPCTSTR lpClassName,
				_In_opt_	LPCTSTR lpWindowName,);
				NTSTATUS NTAPI NtSetInformationProcess(
			    HANDLE ProcessHandle,
			    PROCESS_INFORMATION_CLASS ProcessInformationClass,
			    PVOID ProcessInformation,
			    ULONG ProcessInformationLength);
				NTSTATUS WINAPI ZwQueryInformationProcess(
				_In_	HANDLE ProcessHandle,
				_In_	PROCESSINFOCLASS ProcessInformationClass,
				_Out_	PVOID ProcessInformation,
				_In_	ULONG ProcessInformationLength,
				_Out_opt	PULONG ReturnLength);
			'''

			SetDebugger_Adderss = dbg.func_resolve_debuggee("kernel32.dll", 'IsDebuggerPresent')
			SetInfoProc_Address = dbg.func_resolve_debuggee("ntdll.dll", 'ZwSetInformationProcess')
			SetInfoThread_Address = dbg.func_resolve_debuggee("ntdll.dll", 'ZwSetInformationThread')
			SetQuInfoProc_Address = dbg.func_resolve_debuggee("ntdll.dll", 'ZwQueryInformationProcess')
			SetFindWin_Address = dbg.func_resolve_debuggee("User32.dll", 'FindWindowA')

			if SetDebugger_Adderss: print("SetDebugger_Adderss -> 0x%08x" % SetDebugger_Adderss)
			if SetInfoProc_Address: print("SetInfoProc_Address -> 0x%08x" % SetInfoProc_Address)
			if SetInfoThread_Address: print("SetInfoThread_Address -> 0x%08x" % SetInfoThread_Address)
			if SetQuInfoProc_Address: print("SetQuInfoProc_Address -> 0x%08x" % SetQuInfoProc_Address)
			if SetFindWin_Address: print("SetFindWindow_Address -> 0x%08x" %SetFindWin_Address)

			if SetDebugger_Adderss or SetInfoProc_Address or SetInfoThread_Address or SetQuInfoProc_Address or SetFindWin_Address:
				# if SetInfoProc_Address:
				# 	hooks.add(dbg, SetInfoProc_Address, 4, pass_anti_analysis, None)
				# if SetInfoThread_Address:
				# 	hooks.add(dbg, SetInfoThread_Address, 4, pass_anti_analysis, None)
				# if SetQuInfoProc_Address:
				# 	hooks.add(dbg, SetQuInfoProc_Address, 5, pass_anti_analysis, None)				
				if SetFindWin_Address:
					hooks.add(dbg, SetFindWin_Address, 2, pass_anti_analysis, None)
					print("Hooked at : 0x%08x" % SetFindWin_Address)
					break
				else:
					print("[Error] : couldn't resolve hook address")
					# sys.exit(-1)
	if isProcess:
		print("Waiting for occuring debugger event")
		dbg.run()
	else:
		print("[Error]: There is no process[%s]" % target_name)
		# sys.exit(-1)

