// written by scoward
#include <sstream>

#include <zmq.hpp>

#include <Poco/Thread.h>
#include <Poco/Random.h>

#include "hermes/publisher.h"
#include "hermes/Pulse_generated.h"

namespace hermes
{

struct InternalPulse
{
	InternalPulse(std::uint64_t t, std::uint64_t f, std::uint64_t a,
		      std::uint64_t pw)
		: toa(t)
		, frequency(f)
		, amplitude(a)
		, pulse_width(pw)
	{
	}
	std::uint64_t toa;
	std::uint64_t frequency;
	std::uint64_t amplitude;
	std::uint64_t pulse_width;
};

hermes::InternalPulse getRandomPulse()
{
	Poco::Random r;
	r.seed(0);

	hermes::InternalPulse p(r.next(), r.next(), r.next(), r.next());
	return p;
}

Publisher::Publisher(Poco::Logger &log)
	: hermes::LoggableRunnable(log)
{
}
void Publisher::run()
{
	zmq::context_t context = zmq::context_t(1);

	//  We send updates via this socket
	zmq::socket_t publishSocket = zmq::socket_t(context, ZMQ_PUB);
	publishSocket.bind("tcp://*:5565");

	//  Now broadcast exactly 10 updates with pause
	int update_nbr;
	for (update_nbr = 0; update_nbr < 100; update_nbr++)
	{
		hermes::InternalPulse randomPulse = getRandomPulse();

		flatbuffers::FlatBufferBuilder fbb;
		hermes::PulseBuilder builder(fbb);

		builder.add_toa(randomPulse.toa);
		builder.add_frequency(randomPulse.frequency);
		builder.add_amplitude(randomPulse.amplitude);
		builder.add_pulse_width(randomPulse.pulse_width);

		auto response = builder.Finish();
		fbb.Finish(response);

		std::stringstream ss;
		ss << "Sending Pulse " << update_nbr << "…";
		logger().information(ss.str());
		int buffersize = fbb.GetSize();
		zmq::message_t request(buffersize);
		memcpy((void *)request.data(), fbb.GetBufferPointer(),
		       buffersize);
		publishSocket.send(request);
		logger().information("Pulse sent!");

		Poco::Thread::sleep(1000); // in ms
	}
}

void Publisher::setIp(const std::string &ip)
{
	_ip = ip;
}

} // namespace hermes
// written by scoward