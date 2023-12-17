// written by scoward
#ifndef HERMES_H
#define HERMES_H
#include <string>
#include <memory>

#include <Poco/Util/Application.h>

#include "hermes/LoggableRunnable.h"

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

	void handleRole(const std::string &name, const std::string &value);

	void displayHelp();

	int main(const ArgVec &args);

private:
	bool _helpRequested;
	std::string _roleString;
	std::unique_ptr<hermes::LoggableRunnable> _runnable;
};
} // namespace hermes
#endif // HERMES_H
// written by scoward