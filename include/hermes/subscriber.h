#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

#include <Poco/Runnable.h>

namespace hermes
{

class Subscriber : public Poco::Runnable
{
public:
	Subscriber() = default;
	virtual ~Subscriber() = default;
	virtual void run();

protected:
private:
};
} // namespace hermes
#endif // SUBSCRIBER_H