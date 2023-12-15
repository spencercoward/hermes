// // written by scoward
// //
// // Hermes.cpp
// //
// // This sample demonstrates the Application class.
// //
// // Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// // and Contributors.
// //
// // SPDX-License-Identifier:	BSL-1.0
// //

// #include "Poco/Util/Application.h"
// #include "Poco/Util/Option.h"
// #include "Poco/Util/OptionSet.h"
// #include "Poco/Util/HelpFormatter.h"
// #include "Poco/Util/AbstractConfiguration.h"
// #include "Poco/AutoPtr.h"
// #include <iostream>
// #include <sstream>

// using Poco::AutoPtr;
// using Poco::Util::AbstractConfiguration;
// using Poco::Util::Application;
// using Poco::Util::HelpFormatter;
// using Poco::Util::Option;
// using Poco::Util::OptionCallback;
// using Poco::Util::OptionSet;

// class Hermes : public Application
// {
// public:
// 	Hermes()
// 		: _helpRequested(false)
// 	{
// 	}

// protected:
// 	void initialize(Application &self)
// 	{
// 		loadConfiguration(); // load default configuration files, if present
// 		Application::initialize(self);
// 		// add your own initialization code here
// 	}

// 	void uninitialize()
// 	{
// 		// add your own uninitialization code here
// 		Application::uninitialize();
// 	}

// 	void reinitialize(Application &self)
// 	{
// 		Application::reinitialize(self);
// 		// add your own reinitialization code here
// 	}

// 	void defineOptions(OptionSet &options)
// 	{
// 		Application::defineOptions(options);

// 		options.addOption(
// 			Option("help", "h",
// 			       "display help information on command line arguments")
// 				.required(false)
// 				.repeatable(false)
// 				.callback(OptionCallback<Hermes>(
// 					this, &Hermes::handleHelp)));

// 		options.addOption(
// 			Option("define", "D", "define a configuration property")
// 				.required(false)
// 				.repeatable(true)
// 				.argument("name=value")
// 				.callback(OptionCallback<Hermes>(
// 					this, &Hermes::handleDefine)));
// 	}

// 	void handleHelp(const std::string &name, const std::string &value)
// 	{
// 		_helpRequested = true;
// 		displayHelp();
// 		stopOptionsProcessing();
// 	}

// 	void handleDefine(const std::string &name, const std::string &value)
// 	{
// 		defineProperty(value);
// 	}

// 	void handleConfig(const std::string &name, const std::string &value)
// 	{
// 		loadConfiguration(value);
// 	}

// 	void displayHelp()
// 	{
// 		HelpFormatter helpFormatter(options());
// 		helpFormatter.setCommand(commandName());
// 		helpFormatter.setUsage("OPTIONS");
// 		helpFormatter.setHeader(
// 			"A sample application that demonstrates some of the features of the Poco::Util::Application class.");
// 		helpFormatter.format(std::cout);
// 	}

// 	void defineProperty(const std::string &def)
// 	{
// 		std::string name;
// 		std::string value;
// 		std::string::size_type pos = def.find('=');
// 		if (pos != std::string::npos)
// 		{
// 			name.assign(def, 0, pos);
// 			value.assign(def, pos + 1, def.length() - pos);
// 		} else
// 		{
// 			name = def;
// 		}
// 		config().setString(name, value);
// 	}

// 	int main(const ArgVec &args)
// 	{
// 		if (!_helpRequested)
// 		{
// 			logger().information("Command line:");
// 			std::ostringstream ostr;
// 			for (ArgVec::const_iterator it = argv().begin();
// 			     it != argv().end(); ++it)
// 			{
// 				ostr << *it << ' ';
// 			}
// 			logger().information(ostr.str());
// 			logger().information("Arguments to main():");
// 			for (ArgVec::const_iterator it = args.begin();
// 			     it != args.end(); ++it)
// 			{
// 				logger().information(*it);
// 			}
// 			logger().information("Application properties:");
// 			printProperties("");
// 		}
// 		return Application::EXIT_OK;
// 	}

// 	void printProperties(const std::string &base)
// 	{
// 		AbstractConfiguration::Keys keys;
// 		config().keys(base, keys);
// 		if (keys.empty())
// 		{
// 			if (config().hasProperty(base))
// 			{
// 				std::string msg;
// 				msg.append(base);
// 				msg.append(" = ");
// 				msg.append(config().getString(base));
// 				logger().information(msg);
// 			}
// 		} else
// 		{
// 			for (AbstractConfiguration::Keys::const_iterator it =
// 				     keys.begin();
// 			     it != keys.end(); ++it)
// 			{
// 				std::string fullKey = base;
// 				if (!fullKey.empty())
// 					fullKey += '.';
// 				fullKey.append(*it);
// 				printProperties(fullKey);
// 			}
// 		}
// 	}

// private:
// 	bool _helpRequested;
// };

// POCO_APP_MAIN(Hermes)

// // written by scoward

#include <Poco/Stopwatch.h>
#include "hermes/hermes.h"

int main()
{
	Poco::Stopwatch sw;

	sw.start();
	for (int i(0); i < 0xFFFF; ++i)
	{
		hermes::Pulse p;
	}
	sw.stop();
	return 0;
}