// written by scoward
#include <sstream>
#include <iostream>

#include <zmq.hpp>
#include <flatbuffers/flatbuffers.h>

#include <Poco/NumberFormatter.h>

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
	zmq::context_t context(1);

	//  Connect our subscriber socket
	zmq::socket_t subSocket(context, zmq::socket_type::sub);
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

		auto pulses = hermes::GetPulseMesasge(receiveMessage.data());

		logger().information("\n\nReceived " + Poco::NumberFormatter::format(pulses->pulses()->size()) +
				     " Pulses");

		for (std::size_t i(0); i < pulses->pulses()->size(); ++i)
		{
			auto pulse = (*pulses->pulses())[i];
			logger().information("\n\tReceived Pulse number " + Poco::NumberFormatter::format(i));
			logger().information("\ttoa: " + Poco::NumberFormatter::format(pulse->toa()));
			logger().information("\tfrequency: " + Poco::NumberFormatter::format(pulse->frequency()));
			logger().information("\tamplitude: " + Poco::NumberFormatter::format(pulse->amplitude()));
			logger().information("\tpulse_width: " + Poco::NumberFormatter::format(pulse->pulse_width()));
		}
	}
}

void Subscriber::setIp(const std::string &ip)
{
	_ip = ip;
}

} // namespace hermes
// written by scoward