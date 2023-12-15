// // written by scoward

#include <Poco/Stopwatch.h>
#include <zmq.hpp>
#include "hermes/hermes.h"
#include "hermes/Pulse_generated.h"

int main()
{
	flatbuffers::FlatBufferBuilder builder(1024);

	auto pulse = hermes::CreatePulse(builder, 0, 0, 0, 0);

	Poco::Stopwatch sw;

	sw.start();
	for (int i(0); i < 0xFFFF; ++i)
	{
	}
	sw.stop();
	return 0;
}
// // written by scoward