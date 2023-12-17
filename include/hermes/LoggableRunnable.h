// written by scoward
#ifndef LOGGABLERUNNABLE_H
#define LOGGABLERUNNABLE_H

#include <string>

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
	// FIXME SJC, this doesnt quite seem to fit here, unless i change the name of this class
	virtual void setIp(const std::string &ip) = 0;

private:
	Poco::Logger &_logger;
};

} // namespace hermes
#endif // LOGGABLERUNNABLE_H
// written by scoward