#pragma once
#include "Logger.hpp"

class ConsoleLogger : public Logger
{
public:
	virtual void Log(const std::string& logLevel, const std::string& message) const override;
	virtual void Info(const std::string& message) const override;
	virtual void Error(const std::string& message) const override;
	virtual void Debug(const std::string& message) const override;
};
