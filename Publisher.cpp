#include <zmq.hpp>
#include <zmq_addon.hpp>
#include <string>
#include <sstream>
#include <unistd.h>
#include <iostream>

int main()
{
	int major, minor, patch;
	zmq_version(&major, &minor, &patch);
	std::cout << "ZeroMQ version: " << major << "." << minor << "." << patch << std::endl;

	zmq::context_t context(1);
	zmq::socket_t socket(context, ZMQ_PUB);

	// Client public and secret keys
	std::string client_secret_key = "([okSRthFC2y.BQZN.ok354Yuq2&spWF6$h3XKV^";
	std::string client_public_key = "zeo0IQVzLE1&xv:D*dv&>*N^V3}h7S:+5lK^7<{d";

	// Server public key
	std::string server_public_key = "9L6%1bGNi=h@B4)Ro$4Qvqzh=Oo%WXz8H1ZJ:SR/";
	std::string server_secret_key = "&H/{KjMobYp0>TibUtvTX?WwJR>vZZJyg0>{}m}V";

	socket.setsockopt(ZMQ_CURVE_SERVER, 1);
	socket.setsockopt(ZMQ_CURVE_SECRETKEY, server_secret_key.c_str(),server_secret_key.length());
	//socket.setsockopt(ZMQ_CURVE_PUBLICKEY, server_public_key);
	//socket.setsockopt(ZMQ_CURVE_SERVERKEY, client_public_key);

	socket.bind("tcp://0.0.0.0:5555");

	while (true)
	{
		std::ostringstream oss;
		std::string message = "Hello, this is a message";

		zmq::message_t zmq_message(message.size());
		memcpy(zmq_message.data(), message.data(), message.size());
		std::cout << "Send" << std::endl;
		socket.send(zmq_message, zmq::send_flags::none);
		sleep(0.1); // Send every 5 seconds
	}

	return 0;
}
