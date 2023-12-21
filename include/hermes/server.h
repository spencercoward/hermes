// written by scoward
#ifndef SERVER_H
#define SERVER_H

#include "hermes/LoggableRunnable.h"

namespace hermes
{

class Server : public hermes::LoggableRunnable
{
public:
	Server(Poco::Logger &log);
	virtual ~Server() = default;
	virtual void run();
	virtual void setIp(const std::string &ip);

protected:
	std::string _ip;

private:
};

} // namespace hermes
#endif // SERVER_H
// written by scoward