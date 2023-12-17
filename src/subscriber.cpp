// written by scoward
#include <sstream>

#include <zmq.hpp>
#include <flatbuffers/flatbuffers.h>

#include "hermes/subscriber.h"

#include "hermes/Pulse_generated.h"

namespace hermes
{
Subscriber::Subscriber(Poco::Logger &log)
	: hermes::LoggableRunnable(log)
{
}

void Subscriber::run()
{
	zmq::context_t context = zmq::context_t(1);

	//  Connect our subscriber socket
	zmq::socket_t subSocket = zmq::socket_t(context, ZMQ_SUB);
	subSocket.setsockopt(ZMQ_IDENTITY, "Hello", 5);
	subSocket.setsockopt(ZMQ_SUBSCRIBE, "", 0);
	subSocket.connect("tcp://localhost:5565");

	//  Get updates, expect random Ctrl-C death
	while (1)
	{
		zmq::message_t receiveMessage;
		subSocket.recv(&receiveMessage);

		flatbuffers::FlatBufferBuilder fbb;
		hermes::PulseBuilder builder(fbb);

		auto pulse = hermes::GetPulse(receiveMessage.data());

		std::stringstream ss;
		ss << "Received Pulse\n";
		logger().information(ss.str());
		ss.clear();
		ss << "toa: " << pulse->toa() << "\n";
		logger().information(ss.str());
		ss.clear();
		ss << "frequency: " << pulse->frequency() << "\n";
		logger().information(ss.str());
		ss.clear();
		ss << "amplitude: " << pulse->amplitude() << "\n";
		logger().information(ss.str());
		ss.clear();
		ss << "pulse_width: " << pulse->pulse_width() << "\n";
		logger().information(ss.str());
	}
}

void Subscriber::setIp(const std::string &ip)
{
	_ip = ip;
}

} // namespace hermes
// written by scoward