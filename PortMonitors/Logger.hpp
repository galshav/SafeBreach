#pragma once
#include <string>

class Logger
{
public:
	virtual void Log(const std::string& logLevel, const std::string& message) const = 0;
	virtual void Info(const std::string& message) const = 0;
	virtual void Error(const std::string& message) const = 0;
	virtual void Debug(const std::string& message) const = 0;

private:
};