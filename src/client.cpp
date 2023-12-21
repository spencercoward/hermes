// written by scoward
#include <sstream>
#include <iostream>

#include <zmq.hpp>
#include <flatbuffers/flatbuffers.h>

#include <Poco/NumberFormatter.h>

#include "hermes/client.h"
#include "hermes/Pulse_generated.h"

namespace hermes
{
Client::Client(Poco::Logger &log, const std::string &id)
	: hermes::LoggableRunnable(log)
	, _ip("")
	, _id(id)
{
}

void Client::run()
{
	zmq::context_t context(1);

	//  Connect our client socket
	zmq::socket_t subSocket(context, zmq::socket_type::dealer);
	subSocket.setsockopt(ZMQ_IDENTITY, _id.c_str(), _id.length());
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
		logger().information("Received Id is " + Poco::NumberFormatter::format(pulses->id()));

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

void Client::setIp(const std::string &ip)
{
	_ip = ip;
}

} // namespace hermes
// written by scoward