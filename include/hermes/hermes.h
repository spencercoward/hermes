#ifndef HERMES_H
#define HERMES_H
#include <iostream>
#include <sstream>
#include <memory>
#include "Poco/Util/Application.h"

namespace hermes
{

class Hermes : public Poco::Util::Application
{
public:
	Hermes();

protected:
	void initialize(Application &self);

	void uninitialize();

	void reinitialize(Application &self);

	void defineOptions(Poco::Util::OptionSet &options);

	void handleHelp(const std::string &name, const std::string &value);

	void handleConfig(const std::string &name, const std::string &value);

	void displayHelp();

	int main(const ArgVec &args);

private:
	bool _helpRequested;
	std::string _roleString;
	std::unique_ptr<Poco::Runnable> _runnable;
};
} // namespace hermes
#endif // HERMES_H