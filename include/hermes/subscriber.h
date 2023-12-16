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

protected:
private:
};
} // namespace hermes
#endif // SUBSCRIBER_H