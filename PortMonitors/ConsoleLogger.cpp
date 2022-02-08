#include "ConsoleLogger.hpp"
#include <iostream>
#include <chrono>
#include <ctime>

void ConsoleLogger::Log(const std::string& logLevel, const std::string& message) const
{
	const auto currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::cout << std::ctime(&currentTime) << logLevel << ": " << message << std::endl;
}

void ConsoleLogger::Info(const std::string& message) const
{
	this->Log("Info", message);
}

void ConsoleLogger::Error(const std::string& message) const
{
	this->Log("Error", message);
}

void ConsoleLogger::Debug(const std::string& message) const
{
	this->Log("Debug", message);
}