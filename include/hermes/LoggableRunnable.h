#ifndef LOGGABLERUNNABLE_H
#define LOGGABLERUNNABLE_H

#include <Poco/Logger.h>
#include <Poco/Runnable.h>

namespace hermes
{

class LoggableRunnable : public Poco::Runnable
{
public:
	LoggableRunnable(Poco::Logger &log)
		: _logger(log)
	{
	}

	Poco::Logger &logger()
	{
		return _logger;
	}

private:
	Poco::Logger &_logger;
};
} // namespace hermes
#endif // LOGGABLERUNNABLE_H