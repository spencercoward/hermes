#ifndef PUBLISHER_H
#define PUBLISHER_H

#include <Poco/Runnable.h>

namespace hermes
{

class Publisher : public Poco::Runnable
{
public:
	Publisher() = default;
	virtual ~Publisher() = default;
	virtual void run();

protected:
private:
};
} // namespace hermes
#endif // PUBLISHER_H