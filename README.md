# Add Monitor persistence technique
[Mitre reference](https://attack.mitre.org/techniques/T1547/010/)

[Halpful resource](https://stmxcsr.com/persistence/print-monitor.html)

## Usage
    PrintMonitor.exe [1, 2]
        1. Install.
        2. Remove.

## AV Signature surface:
There is 2 ways to implement the persistence method.
1. Using AddMonitor WinApi.
2. Directly modify the registry.

I've decided to create 2 executable from the same codebase using preprocessing macros (#ifdef, #if, etc..)
This is good choice since i want to be able to split the malicious behavior and decoupling the 2 techniques from each other.
If some security product only sign the registry edit, it wont catch the add monitor call, and vice-versa.
Also, this can be bypassed by some other noise/obfuscations that I don't have time to implement here.

The specfic method can be adjusted by specifing 2 different env variables before compilation. defining them both would caouse redefinition compile time error, specify none would cause unresolved external linker error.
so only one choice is accaptable (mutally exclusive compile time restriction).

## Limitations:
The app must run as administrator privileges at least.
This is due to the fact that [AddMonitor](https://docs.microsoft.com/en-us/windows/win32/printdocs/addmonitor) require SeLoadDriverPrivilege privilege constant.
This is mandatory beacuse the actual code that register the dll is the spoolsrv.exe executable which run under system priviligeses.
Even after running with desired account, We muse assure that the privilege is enabled. In Windows you can examine the list of privileges of specific token using the [GetTokenInformation](https://docs.microsoft.com/en-us/windows/win32/api/securitybaseapi/nf-securitybaseapi-gettokeninformation) WinApi.
and specify the TokenPrivileges enum value for the TokenInformationClass member.
You will notice that the required privilege is not even exist if running by process with low access token.
Anyway, We must enable it, since it disabled by default.

The DLL which deployed to the %systemroot%/System32 directory must expose some functions in order the method to work. specifically it must export (by .def file or __declspec(dllexport)) the [InitializePrintMonitor2](https://docs.microsoft.com/en-us/windows-hardware/drivers/ddi/winsplp/nf-winsplp-initializeprintmonitor2)
I got 127 error code when i didn't know about the functions i must implement. which is error with the following description "The specified procedure could not be found".
Although, DLLEntry did get call as from the procmon log, the spoolsrv.exe terminated it quickly.