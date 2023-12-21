// written by scoward
#include <iostream>

#include <Poco/Util/Option.h>
#include <Poco/Util/OptionSet.h>
#include <Poco/Util/HelpFormatter.h>
#include <Poco/AutoPtr.h>
#include <Poco/ConsoleChannel.h>

#include "hermes/hermes.h"
#include "hermes/server.h"
#include "hermes/client.h"

namespace hermes
{

Hermes::Hermes()
	: _helpRequested(false)
	, _roleString("")
	, _runnable(nullptr)
{
}

void Hermes::initialize(Application &self)
{
	Application::initialize(self);
	// add your own initialization code here
	Poco::AutoPtr<Poco::ColorConsoleChannel> pCCC = new Poco::ColorConsoleChannel;
	logger().setChannel("", pCCC);
}

void Hermes::uninitialize()
{
	// add your own uninitialization code here
	Application::uninitialize();
}

void Hermes::reinitialize(Application &self)
{
	Application::reinitialize(self);
	// add your own reinitialization code here
}

void Hermes::defineOptions(Poco::Util::OptionSet &options)
{
	Application::defineOptions(options);

	options.addOption(Poco::Util::Option("help", "h", "display help information on command line arguments")
				  .required(false)
				  .repeatable(false)
				  .callback(Poco::Util::OptionCallback<Hermes>(this, &Hermes::handleHelp)));

	options.addOption(Poco::Util::Option("role", "r", "role to use [pub/sub]")
				  .required(true)
				  .repeatable(false)
				  .argument("value")
				  .callback(Poco::Util::OptionCallback<Hermes>(this, &Hermes::handleRole)));

	options.addOption(
		Poco::Util::Option("ipaddr", "i", "ip addr to send/receive on").required(false).repeatable(false));
}

void Hermes::handleHelp(const std::string &name, const std::string &value)
{
	_helpRequested = true;
	displayHelp();
	stopOptionsProcessing();
}

void Hermes::handleRole(const std::string &name, const std::string &value)
{
	_roleString = value;
}

void Hermes::displayHelp()
{
	Poco::Util::HelpFormatter helpFormatter(options());
	helpFormatter.setCommand(commandName());
	helpFormatter.setUsage("OPTIONS");
	helpFormatter.setHeader("Example Pub Sub application using FlatBuffers and ZeroMQ");
	helpFormatter.format(std::cout);
}

int Hermes::main(const ArgVec &args)
{
	if (!_helpRequested)
	{
		if (_roleString == "pub")
		{
			_runnable.reset(new hermes::Server(logger()));
		}
		else if (_roleString == "sub1")
		{
			_runnable.reset(new hermes::Client(logger(), _roleString));
		}
		else if (_roleString == "sub2")
		{
			_runnable.reset(new hermes::Client(logger(), _roleString));
		}
		else
		{
			logger().fatal("role parameter provided is not acceptable, must be pub or sub, you provided [" +
				       _roleString + "]");
			return Poco::Util::Application::EXIT_USAGE;
		}

		_runnable->run();
	}
	return Application::EXIT_OK;
}

} // namespace hermes

POCO_APP_MAIN(hermes::Hermes)

// written by scoward