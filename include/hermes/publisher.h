// written by scoward
#ifndef PUBLISHER_H
#define PUBLISHER_H

#include "hermes/LoggableRunnable.h"

namespace hermes
{

class Publisher : public hermes::LoggableRunnable
{
public:
	Publisher(Poco::Logger &log);
	virtual ~Publisher() = default;
	virtual void run();
	virtual void setIp(const std::string &ip);

protected:
	std::string _ip;

private:
};

} // namespace hermes
#endif // PUBLISHER_H
// written by scoward