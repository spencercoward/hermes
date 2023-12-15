// // written by scoward

#include <Poco/Stopwatch.h>
#include <zmq.h>
#include "hermes/hermes.h"

int main()
{
	Poco::Stopwatch sw;

	sw.start();
	for (int i(0); i < 0xFFFF; ++i)
	{
		hermes::Pulse p;
	}
	sw.stop();
	return 0;
}
// // written by scoward