#include <Windows.h>
#include "WinAPI.hpp"
#include <exception>
#include <iostream>
void Persistency::PortMonitor::WinAPI::InstallByAddMonitor()
{
	MONITOR_INFO_2W monitorInfo = { 0 };
	//TCHAR env[12] = TEXT("Windows x64");
	//TCHAR name[12] = TEXT("Monitor");
	//TCHAR dll[12] = TEXT("StubDLL.dll");
	monitorInfo.pName = (LPWSTR)L"Monitor";
	monitorInfo.pEnvironment = NULL;
	monitorInfo.pDLLName = (LPWSTR)L"StubDLL.dll";

	const BOOL addMonitorResult = AddMonitorW(NULL, 2, (LPBYTE)&monitorInfo);
	if (0 == addMonitorResult)
	{
		throw std::exception("AddMonitor fail.");
	}
}

void Persistency::PortMonitor::WinAPI::RemoveByDeleteMonitor()
{
	MONITOR_INFO_2W monitorInfo = { 0 };
	monitorInfo.pName = (LPWSTR)L"Monitor";
	monitorInfo.pEnvironment = (LPWSTR)"Windows x64";
	monitorInfo.pDLLName = (LPWSTR)L"StubDLL.dll";

	const BOOL result = DeleteMonitorW(NULL, NULL, (LPWSTR)L"Monitor");
	std::cout << GetLastError() << std::endl;
}

/*
*	I may change return value later to void, not sure right now since I throw an exception when things dont work.
*/
bool Persistency::PortMonitor::WinAPI::CheckRequiredPrivilegeForPortMonitor()
{
	HANDLE processToken = NULL;
	if (0 == OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY | TOKEN_ADJUST_PRIVILEGES, &processToken))
	{
		throw std::exception("Can not get process token.");
	}

	LUID luid = { 0 };
	LookupPrivilegeValueW(NULL, SE_LOAD_DRIVER_NAME, &luid);
	PRIVILEGE_SET privilegeSet = { 0 };
	privilegeSet.PrivilegeCount = 1;
	privilegeSet.Control = PRIVILEGE_SET_ALL_NECESSARY;
	privilegeSet.Privilege[0].Luid = luid;
	privilegeSet.Privilege[0].Attributes = SE_PRIVILEGE_ENABLED;
	TOKEN_PRIVILEGES tokenPrivileges = { 0 };
	tokenPrivileges.PrivilegeCount = 1;
	tokenPrivileges.Privileges[0] = privilegeSet.Privilege[0];
	if (!AdjustTokenPrivileges(processToken, FALSE, &tokenPrivileges, sizeof(TOKEN_PRIVILEGES), (PTOKEN_PRIVILEGES)NULL, (PDWORD)NULL))
	{
		std::cout << "AdjustTokenPrivileges fail with error: " << GetLastError() << std::endl;
		throw std::exception("Can not enable token privilege to SE_LOAD_DRIVER_NAME");
	}

	if (ERROR_NOT_ALL_ASSIGNED == GetLastError())
	{
		throw std::exception("token does not have specified privilege");
	}

	//BOOL granted = FALSE;
	//std::cout << "granted: " << granted << std::endl;
	//const BOOL privCheckReturnValue = PrivilegeCheck(processToken, &privilegeSet, &granted);
	//return granted;
	return true;
}

