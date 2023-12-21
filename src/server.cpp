// written by scoward
#include <sstream>

#include <zmq.hpp>

#include <Poco/Thread.h>
#include <Poco/Random.h>
#include <Poco/DateTime.h>
#include <Poco/NumberFormatter.h>

#include "hermes/server.h"
#include "hermes/Pulse_generated.h"

namespace hermes
{
/// @brief Internal format of what a pulse is to us
struct InternalPulse
{
	InternalPulse(std::uint64_t t, std::uint64_t f, std::uint64_t a, std::uint64_t pw)
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

/// @brief Creates a vector of pulses based on our internal format
/// @return std::vector<hermes::InternalPulse>
std::vector<hermes::InternalPulse> getRandomPulses()
{
	::flatbuffers::FlatBufferBuilder builder;

	// used to get random data
	Poco::Random r;
	// used to get a seed based on the current time
	Poco::DateTime now;

	// setup a random that will allow us to populate the pulse with random data
	r.seed(now.microsecond());
	std::vector<hermes::InternalPulse> pulsesVector;

	for (std::size_t i(0); i < 2; ++i)
	{
		pulsesVector.push_back(hermes::InternalPulse(r.next(), r.next(), r.next(), r.next()));
	}
	return pulsesVector;
}

Server::Server(Poco::Logger &log)
	: hermes::LoggableRunnable(log)
{
}

void Server::run()
{
	zmq::context_t context(1);

	//  We send updates via this socket
	zmq::socket_t pubSocket(context, zmq::socket_type::router);
	pubSocket.bind("tcp://*:5565");

	flatbuffers::FlatBufferBuilder fbb;
	//  Now broadcast exactly 100 updates with pause
	for (int update_nbr = 0; update_nbr < 100; update_nbr++)
	{
		auto pulsesVec = getRandomPulses();

		// vector of Pulses to be sent on the wire
		std::vector<flatbuffers::Offset<hermes::Pulse> > pulseOffsets;

		// Create hermes::Pulses for the wire based on our InternalPulses that we have
		for (auto pulse : pulsesVec)
		{
			pulseOffsets.push_back(hermes::CreatePulse(fbb, pulse.toa, pulse.frequency, pulse.amplitude,
								   pulse.pulse_width));
		}

		// create a vector from the vector of pulse offsets
		// Note: we are saving this here rather than just calling it below is because it must be above when we
		// instantiate hermes::PulseMessageBuilder
		auto pulsesVectorOffset = fbb.CreateVector(pulseOffsets);

		// this must be below the CreatePulse call and CreateVector call or else its nested and thats not allowed
		hermes::PulseMesasgeBuilder builder(fbb);

		// ddd the pulses to the PulseMesasgeBuilder
		builder.add_pulses(pulsesVectorOffset);
		builder.add_id(update_nbr);

		// finish the builders
		auto response = builder.Finish();
		fbb.Finish(response);

		logger().information("Sending Pulses iteration " + Poco::NumberFormatter::format(update_nbr) + "…");

		// create and send the zmq message
		zmq::message_t message(fbb.GetBufferPointer(), fbb.GetSize());
		if (update_nbr % 2)
		{
			zmq::message_t identity("sub1", 4);
			pubSocket.send(identity, zmq::send_flags::sndmore);
		}
		else
		{
			zmq::message_t identity("sub2", 4);
			pubSocket.send(identity, zmq::send_flags::sndmore);
		}
		pubSocket.send(message, zmq::send_flags::none);

		logger().information("Pulses sent!");

		Poco::Thread::sleep(1000); // in ms

		// clear the buffer after each send
		fbb.Clear();
	}
}

void Server::setIp(const std::string &ip)
{
	_ip = ip;
}

} // namespace hermes
// written by scoward