#include <zmq.hpp>

#include "hermes/subscriber.h"

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
		StarBufferBuilder builder(fbb);

		auto star = GetStarBuffer(receiveMessage.data());

		logger().information("Received Star");
		logger().information("radius: " << star->radius());
		logger().information("mass: " << star->mass());
		logger().information("volume: " << star->volume());
	}
}

} // namespace hermes