#pragma once
namespace Persistency
{
	namespace PortMonitor
	{
		namespace WinAPI
		{
			void InstallByAddMonitor();
			bool CheckRequiredPrivilegeForPortMonitor();
			void RemoveByDeleteMonitor();
		}
	}
}