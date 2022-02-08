#include "pch.h"

#define HKEYMONITOR HKEY

typedef struct _BINARY_CONTAINER {
	DWORD cbBuf;
	LPBYTE pData;
} BINARY_CONTAINER, * PBINARY_CONTAINER;

typedef struct _BIDI_DATA {
	DWORD dwBidiType;
	union {
		BOOL   bData;
		LONG   iData;
		LPWSTR sData;
		FLOAT  fData;
		BINARY_CONTAINER biData;
	}u;
} BIDI_DATA, * PBIDI_DATA, * LPBIDI_DATA;

typedef struct _BIDI_RESPONSE_DATA {
	DWORD  dwResult;
	DWORD  dwReqNumber;
	LPWSTR pSchema;
	BIDI_DATA data;
} BIDI_RESPONSE_DATA, * PBIDI_RESPONSE_DATA, * LPBIDI_RESPONSE_DATA;

typedef struct _BIDI_RESPONSE_CONTAINER {
	DWORD Version;
	DWORD Flags;
	DWORD Count;
	BIDI_RESPONSE_DATA aData[1];
} BIDI_RESPONSE_CONTAINER, * PBIDI_RESPONSE_CONTAINER, * LPBIDI_RESPONSE_CONTAINER;

typedef struct _BIDI_REQUEST_DATA {
	DWORD     dwReqNumber;
	LPWSTR    pSchema;
	BIDI_DATA data;
} BIDI_REQUEST_DATA, * PBIDI_REQUEST_DATA, * LPBIDI_REQUEST_DATA;

typedef struct _BIDI_REQUEST_CONTAINER {
	DWORD Version;
	DWORD Flags;
	DWORD Count;
	BIDI_REQUEST_DATA aData[1];
}BIDI_REQUEST_CONTAINER, * PBIDI_REQUEST_CONTAINER, * LPBIDI_REQUEST_CONTAINER;

typedef struct _MONITORREG {
	DWORD cbSize;
	LONG(*fpCreateKey)(HKEYMONITOR hcKey, LPCTSTR pszSubKey, DWORD dwOptions, REGSAM samDesired, PSECURITY_ATTRIBUTES pSecurityAttributes, HKEYMONITOR* phckResult, PDWORD pdwDisposition, HANDLE hSpooler);
	LONG(*fpOpenKey)(HKEYMONITOR hcKey, LPCTSTR pszSubKey, REGSAM samDesired, HKEYMONITOR* phkResult, HANDLE hSpooler);
	LONG(*fpCloseKey)(HKEYMONITOR hcKey, HANDLE hSpooler);
	LONG(*fpDeleteKey)(HKEYMONITOR hcKey, LPCTSTR pszSubKey, HANDLE hSpooler);
	LONG(*fpEnumKey)(HKEYMONITOR hcKey, DWORD dwIndex, LPTSTR pszName, PDWORD pcchName, PFILETIME pftLastWriteTime, HANDLE hSpooler);
	LONG(*fpQueryInfoKey)(HKEYMONITOR hcKey, PDWORD pcSubKeys, PDWORD pcbKey, PDWORD pcValues, PDWORD pcbValue, PDWORD pcbData, PDWORD pcbSecurityDescriptor, PFILETIME pftLastWriteTime, HANDLE hSpooler);
	LONG(*fpSetValue)(HKEYMONITOR hcKey, LPCTSTR pszValue, DWORD dwType, const BYTE* pData, DWORD cbData, HANDLE hSpooler);
	LONG(*fpDeleteValue)(HKEYMONITOR hcKey, LPCTSTR pszValue, HANDLE hSpooler);
	LONG(*fpEnumValue)(HKEYMONITOR hcKey, DWORD dwIndex, LPTSTR pszValue, PDWORD pcbValue, PDWORD pTyp, PBYTE pData, PDWORD pcbData, HANDLE hSpooler);
	LONG(*fpQueryValue)(HKEYMONITOR hcKey, LPCTSTR pszValue, PDWORD pType, PBYTE pData, PDWORD pcbData, HANDLE hSpooler);
} MONITORREG, * PMONITORREG;

typedef struct _MONITORINIT {
	DWORD       cbSize;
	HANDLE      hSpooler;
	HKEYMONITOR hckRegistryRoot;
	PMONITORREG pMonitorReg;
	BOOL        bLocal;
	LPCWSTR     pszServerName;
} MONITORINIT, * PMONITORINIT;

typedef struct _MONITOR2 {
	DWORD  cbSize;
	BOOL(*pfnEnumPorts)(HANDLE hMonitor, LPWSTR pName, DWORD Level, LPBYTE pPorts, DWORD cbBuf, LPDWORD pcbNeeded, LPDWORD pcReturned);
	BOOL(*pfnOpenPort)(HANDLE hMonitor, LPWSTR pName, PHANDLE pHandle);
	BOOL(*pfnOpenPortEx)(HANDLE hMonitor, HANDLE hMonitorPort, LPWSTR pPortName, LPWSTR pPrinterName, PHANDLE pHandle, _MONITOR2* pMonitor2);
	BOOL(*pfnStartDocPort)(HANDLE hPort, LPWSTR pPrinterName, DWORD JobId, DWORD Level, LPBYTE pDocInfo);
	BOOL(*pfnWritePort)(HANDLE hPort, LPBYTE pBuffer, DWORD cbBuf, LPDWORD pcbWritten);
	BOOL(*pfnReadPort)(HANDLE hPort, LPBYTE pBuffer, DWORD cbBuffer, LPDWORD pcbRead);
	BOOL(*pfnEndDocPort)(HANDLE hPort);
	BOOL(*pfnClosePort)(HANDLE hPort);
	BOOL(*pfnAddPort)(HANDLE hMonitor, LPWSTR pName, HWND hWnd, LPWSTR pMonitorName);
	BOOL(*pfnAddPortEx)(HANDLE hMonitor, LPWSTR pName, DWORD Level, LPBYTE lpBuffer, LPWSTR lpMonitorName);
	BOOL(*pfnConfigurePort)(HANDLE hMonitor, LPWSTR pName, HWND hWnd, LPWSTR pPortName);
	BOOL(*pfnDeletePort)(HANDLE hMonitor, LPWSTR pName, HWND hWnd, LPWSTR pPortName);
	BOOL(*pfnGetPrinterDataFromPort)(HANDLE hPort, DWORD ControlID, LPWSTR pValueName, LPWSTR lpInBuffer, DWORD cbInBuffer, LPWSTR lpOutBuffer, DWORD cbOutBuffer, LPDWORD lpcbReturned);
	BOOL(*pfnSetPortTimeOuts)(HANDLE hPort, LPCOMMTIMEOUTS lpCTO, DWORD reserved);
	BOOL(*pfnXcvOpenPort)(HANDLE hMonitor, LPCWSTR pszObject, ACCESS_MASK GrantedAccess, PHANDLE phXcv);
	DWORD(*pfnXcvDataPort)(HANDLE hXcv, LPCWSTR pszDataName, PBYTE pInputData, DWORD cbInputData, PBYTE pOutputData, DWORD cbOutputData, PDWORD pcbOutputNeeded);
	BOOL(*pfnXcvClosePort)(HANDLE hXcv);
	VOID(*pfnShutdown)(HANDLE hMonitor);
	DWORD(*pfnSendRecvBidiDataFromPort)(HANDLE hPort, DWORD dwAccessBit, LPCWSTR pAction, PBIDI_REQUEST_CONTAINER pReqData, PBIDI_RESPONSE_CONTAINER* ppResData);
	DWORD(*pfnNotifyUsedPorts)(HANDLE hMonitor, DWORD cPorts, PCWSTR* ppszPorts);
	DWORD(*pfnNotifyUnusedPorts)(HANDLE hMonitor, DWORD cPorts, PCWSTR* ppszPorts);
	DWORD(*pfnPowerEvent)(HANDLE hMonitor, DWORD event, POWERBROADCAST_SETTING* pSettings);
} MONITOR2, * PMONITOR2, * LPMONITOR2;

BOOL WINAPI CsEnumPorts(HANDLE hMonitor, LPWSTR pName, DWORD Level, LPBYTE pPorts, DWORD cbBuf, LPDWORD pcbNeeded, LPDWORD pcReturned)
{
	// function executes when DLL is loaded
	BOOL bRet = TRUE;

	return bRet;
}

BOOL WINAPI CsOpenPort(HANDLE hMonitor, LPWSTR pName, PHANDLE pHandle)
{
	BOOL bRet = TRUE;

	return bRet;
}

BOOL WINAPI CsOpenPortEx(HANDLE hMonitor, HANDLE hMonitorPort, LPTSTR pszPortName, LPTSTR pszPrinterName, LPHANDLE pHandle, LPMONITOR2 pMonitor)
{
	BOOL bRet = TRUE;

	return bRet;
}

BOOL CsStartDocPort(HANDLE hPort, LPWSTR pPrinterName, DWORD JobId, DWORD Level, LPBYTE pDocInfo)
{
	BOOL bRet = TRUE;

	return bRet;
}

BOOL CsWritePort(HANDLE hPort, LPBYTE pBuffer, DWORD cbBuf, LPDWORD pcbWritten)
{
	BOOL bRet = TRUE;

	return bRet;
}

BOOL CsReadPort(HANDLE hPort, LPBYTE pBuffer, DWORD cbBuffer, LPDWORD pcbRead)
{
	BOOL bRet = TRUE;

	return bRet;
}

BOOL CsEndDocPort(HANDLE hPort)
{
	BOOL bRet = TRUE;

	return bRet;
}

BOOL CsClosePort(HANDLE hPort)
{
	BOOL bRet = TRUE;

	return bRet;
}

BOOL CsGetPrinterDataFromPort(HANDLE hPort, DWORD ControlID, LPWSTR pValueName, LPWSTR lpInBuffer, DWORD cbInBuffer, LPWSTR lpOutBuffer, DWORD cbOutBuffer, LPDWORD lpcbReturned)
{
	BOOL bRet = TRUE;

	return bRet;
}

BOOL CsSetPortTimeOuts(HANDLE hPort, LPCOMMTIMEOUTS lpCTO, DWORD reserved)
{
	BOOL bRet = TRUE;

	return bRet;
}

BOOL WINAPI CsXcvOpenPort(HANDLE hMonitor, LPCWSTR pszObject, ACCESS_MASK GrantedAccess, PHANDLE phXcv)
{
	BOOL bRet = TRUE;

	return bRet;
}

DWORD CsXcvDataPort(HANDLE hXcv, LPCWSTR pszDataName, PBYTE pInputData, DWORD cbInputData, PBYTE pOutputData, DWORD cbOutputData, PDWORD pcbOutputNeeded)
{
	// ERROR_SUCESS
	return 0;
}

BOOL CsXcvClosePort(HANDLE hXcv)
{
	BOOL bRet = TRUE;

	return bRet;
}

VOID CsShutdown(HANDLE hMonitor)
{

}

DWORD CsSendRecvBidiDataFromPort(HANDLE hPort, DWORD dwAccessBit, LPCWSTR pAction, PBIDI_REQUEST_CONTAINER pReqData, PBIDI_RESPONSE_CONTAINER* ppResData)
{
	// ERROR_SUCCESS
	return 0;
}

MONITOR2 Moni =
{
	sizeof(MONITOR2),
	CsEnumPorts, // EnumPorts
	CsOpenPort, // OpenPort
	CsOpenPortEx, // OpenPortEx
	CsStartDocPort, // StatDocPort
	CsWritePort, // WritePort
	CsReadPort, // ReadPort
	CsEndDocPort, // EndDocPort
	CsClosePort, // ClosePort
	NULL, // AddPort -> obsolete should not be used
	NULL, // AddoPortEx -> obsolete must be NULL
	NULL, // ConfigurePort -> obsolete should not be used
	NULL, // DeletePort -> obsolete should not be used
	CsGetPrinterDataFromPort, // GetPrinterDataFromPort
	CsSetPortTimeOuts, // SetPortTimeOuts
	CsXcvOpenPort, // XcvOpenPort | Port Monitors Only
	CsXcvDataPort, // XcvDataPort | Port Monitors Only
	CsXcvClosePort, // XcvClosePort | Port Monitors Only
	CsShutdown, // Shutdown
	CsSendRecvBidiDataFromPort, // SendRecvBidiDataFromPort
	NULL, // NotifyUsedPorts
	NULL, // NotifyUnusedPorts
	NULL  // PowerEvent
};

extern "C" __declspec(dllexport) LPMONITOR2 InitializePrintMonitor2(PMONITORINIT pMonitorInit, PHANDLE phMonitor)
{
	// debug
	CHAR msgbuf[50];
	sprintf_s(msgbuf, 50, "[+] InitializePrintMonitor2 was called");
	::OutputDebugStringA(msgbuf);

	*phMonitor = (PHANDLE)pMonitorInit;

	return &Moni;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		CHAR msgbuf[50];
		sprintf_s(msgbuf, 50, "[+] DLL_PROCESS_ATTACH");
		::OutputDebugStringA(msgbuf);
		break;
	case DLL_THREAD_ATTACH:
	case DLL_PROCESS_DETACH:
	case DLL_THREAD_DETACH:
		break;
	}

	return TRUE;
}