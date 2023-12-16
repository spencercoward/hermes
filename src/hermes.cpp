// // written by scoward

#include <zmq.hpp>

#include <Poco/Util/Option.h>
#include <Poco/Util/OptionSet.h>
#include <Poco/Util/HelpFormatter.h>
#include <Poco/AutoPtr.h>
#include <Poco/ConsoleChannel.h>

#include "hermes/hermes.h"
#include "hermes/Pulse_generated.h"

namespace hermes
{

Hermes::Hermes()
	: _helpRequested(false)
{
}

void Hermes::initialize(Application &self)
{
	Application::initialize(self);
	// add your own initialization code here
	Poco::AutoPtr<Poco::ColorConsoleChannel> pCCC =
		new Poco::ColorConsoleChannel;
	// pCCC->setProperty("traceColor", "");
	// pCCC->setProperty("debugColor", "");
	// pCCC->setProperty("informationColor", "");
	// pCCC->setProperty("noticeColor", "");
	// pCCC->setProperty("warningColor", "");
	// pCCC->setProperty("errorColor", "");
	// pCCC->setProperty("criticalColor", "");
	// pCCC->setProperty("fatalColor", "");
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

	options.addOption(
		Poco::Util::Option(
			"help", "h",
			"display help information on command line arguments")
			.required(false)
			.repeatable(false)
			.callback(Poco::Util::OptionCallback<Hermes>(
				this, &Hermes::handleHelp)));

	options.addOption(
		Poco::Util::Option("role", "r", "role to use [pub/sub]")
			.required(true)
			.repeatable(false)
			.callback(Poco::Util::OptionCallback<Hermes>(
				this, &Hermes::handleConfig)));

	options.addOption(
		Poco::Util::Option("ipaddr", "i", "ip addr to send/receive on")
			.required(false)
			.repeatable(false));
}

void Hermes::handleHelp(const std::string &name, const std::string &value)
{
	_helpRequested = true;
	displayHelp();
	stopOptionsProcessing();
}

void Hermes::handleConfig(const std::string &name, const std::string &value)
{
	_roleString = value;
}

void Hermes::displayHelp()
{
	Poco::Util::HelpFormatter helpFormatter(options());
	helpFormatter.setCommand(commandName());
	helpFormatter.setUsage("OPTIONS");
	helpFormatter.setHeader(
		"Example Pub Sub application using FlatBuffers and ZeroMQ");
	helpFormatter.format(std::cout);
}

int Hermes::main(const ArgVec &args)
{
	if (!_helpRequested)
	{
		logger().information("Command line:");
		std::ostringstream ostr;
		for (ArgVec::const_iterator it = argv().begin();
		     it != argv().end(); ++it)
		{
			ostr << *it << ' ';
		}
		logger().information(ostr.str());
		logger().information("Arguments to main():");
		for (ArgVec::const_iterator it = args.begin(); it != args.end();
		     ++it)
		{
			logger().information(*it);
		}
	}
	return Application::EXIT_OK;
}

} // namespace hermes

POCO_APP_MAIN(hermes::Hermes)

// // written by scoward