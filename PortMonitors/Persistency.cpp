#include "Persistency.hpp"

#if !defined(InstallByWinAPI) && !defined(InstallByRegistryModify)
#error "Please specify installation method."
#endif

#ifdef InstallByWinAPI
#include "WinAPI.hpp"
void  Persistency::PortMonitor::install(const Logger& logger)
{
	logger.Info("Install using WinApi AddMonitpr.");
	const bool granted = Persistency::PortMonitor::WinAPI::CheckRequiredPrivilegeForPortMonitor();
	Persistency::PortMonitor::WinAPI::InstallByAddMonitor();
}

void Persistency::PortMonitor::remove(const Logger& logger)
{
	logger.Info("Remove by calling WinApi DeleteMonitor.");
	const bool granted = Persistency::PortMonitor::WinAPI::CheckRequiredPrivilegeForPortMonitor();
	Persistency::PortMonitor::WinAPI::RemoveByDeleteMonitor();
}
#endif

#ifdef InstallByRegistryModify
#include "Registry.hpp"
void Persistency::PortMonitor::install(const Logger& logger)
{
	logger.Info("Install be direct modify registry.");
	Persistency::Registry::InstallByModifyRegistry();
}

void Persistency::PortMonitor::remove(const Logger& logger)
{
	logger.Info("Remove printer monitor registry key.");
	Persistency::Registry::RemoveByModifyRegistry();
}
#endif