// written by scoward
#ifndef CLIENT_H
#define CLIENT_H

#include "hermes/LoggableRunnable.h"

namespace hermes
{

class Client : public hermes::LoggableRunnable
{
public:
	Client(Poco::Logger &log, const std::string &id);
	virtual ~Client() = default;
	virtual void run();
	virtual void setIp(const std::string &ip);

protected:
	std::string _ip;
	std::string _id;

private:
};

} // namespace hermes
#endif // CLIENT_H
// written by scoward