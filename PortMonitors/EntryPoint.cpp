#include <iostream>
#include <exception>
#include "Logger.hpp"
#include <Windows.h>
#include <string>
#include "ConsoleLogger.hpp"
#include "Persistency.hpp"

char _binary_C__dev_SafeBreach_x64_Debug_StubDLL_dll_start;
char _binary_C__dev_SafeBreach_x64_Debug_StubDLL_dll_end;

enum ErrorLevel : size_t
{
	SUCCESS = 0,
	FAILURE = 1,
	UNHANDLED_EXCEPTION = 2,
};

void PrintUsage()
{
	std::cout << "PortMonitors.exe [1 - Install, 2 - Remove]" << std::endl;
}

/*
* Please read the README.md
* The following codebase contain two implementations for PortMonitor persistence technique.
*	- Using WinAPI function AddMonitor().
*	- Using raw registry manipulation.
* In order to bypass static analysis, and to reduce the signature surface of my final executable
* I use different compilation flags to CL.exe to create two different binaries, one for each method.
* This can be done by specifying the /D flag (see project properties and builder code).
*/
int main(const size_t argc, const char* const* const argv)
{
	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);
	
	ConsoleLogger logger = ConsoleLogger();
	try
	{
		if (2 != argc)
		{
			PrintUsage();
			throw std::exception("Invalid argumetns.");
		}

		logger.Info("App started.");
		const int choice = atoi(argv[1]);
		switch (choice)
		{
		case 1:
		{
			Persistency::PortMonitor::install(logger);
			break;
		}

		case 2:
		{
			Persistency::PortMonitor::remove(logger);
			break;
		}

		default: 
		{
			break;
		}
		}
		
		return ErrorLevel::SUCCESS;
	}

	catch (const std::exception& error)
	{
		std::cout << "Last Error: " << GetLastError() << std::endl; // TODO: use logger.Debug().
		logger.Error(error.what());
		return ErrorLevel::FAILURE;
	}

	catch (...)
	{
		logger.Error("Unhandled exception.");
		return ErrorLevel::UNHANDLED_EXCEPTION;
	}
}