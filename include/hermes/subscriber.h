// written by scoward
#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

#include "hermes/LoggableRunnable.h"

namespace hermes
{

class Subscriber : public hermes::LoggableRunnable
{
public:
	Subscriber(Poco::Logger &log);
	virtual ~Subscriber() = default;
	virtual void run();
	virtual void setIp(const std::string &ip);

protected:
	std::string _ip;

private:
};

} // namespace hermes
#endif // SUBSCRIBER_H
// written by scoward