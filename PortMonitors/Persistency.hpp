#pragma once
#include "Logger.hpp"

namespace Persistency {
namespace PortMonitor {

	void install(const Logger& logger);
	void remove(const Logger& logger);

} // PortMonitor
} // Persistency