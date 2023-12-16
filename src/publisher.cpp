
#include <zmq.hpp>

#include "hermes/publisher.h"

namespace hermes
{
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
		Star randomStar = getRandomStar();

		flatbuffers::FlatBufferBuilder fbb;
		StarBufferBuilder builder(fbb);

		builder.add_radius(randomStar.radius);
		builder.add_mass(randomStar.mass);
		builder.add_volume(randomStar.volume);

		auto response = builder.Finish();
		fbb.Finish(response);

		logger().information("Sending Star " << update_nbr << "…");
		int buffersize = fbb.GetSize();
		zmq::message_t request(buffersize);
		memcpy((void *)request.data(), fbb.GetBufferPointer(),
		       buffersize);
		publishSocket.send(request);
		std::cout << "Star sent!" << std::endl;

		sleep(1);
	}
} // namespace hermes