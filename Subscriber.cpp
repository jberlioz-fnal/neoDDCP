#include <zmq.hpp>
#include <zmq_addon.hpp>
#include <string>
#include <iostream>
#include <thread>
#include <unistd.h>

int main()
{
	sleep(3);
	zmq::context_t context(1);
	zmq::socket_t socket(context, ZMQ_SUB);

	// Client public and secret keys
	std::string client_secret_key = "([okSRthFC2y.BQZN.ok354Yuq2&spWF6$h3XKV^";
	std::string client_public_key = "zeo0IQVzLE1&xv:D*dv&>*N^V3}h7S:+5lK^7<{d";

	// Server public key
	std::string server_public_key = "9L6%1bGNi=h@B4)Ro$4Qvqzh=Oo%WXz8H1ZJ:SR/";
	std::string server_secret_key = "&H/{KjMob2p0>TibUtvTX?WwJR>vZZJyg0>{}m}V";

	socket.setsockopt(ZMQ_CURVE_SERVER, 0);
	socket.setsockopt(ZMQ_CURVE_SECRETKEY, client_secret_key.c_str(),client_secret_key.length());
	socket.setsockopt(ZMQ_CURVE_PUBLICKEY, client_public_key.c_str(), client_public_key.length());
	socket.setsockopt(ZMQ_CURVE_SERVERKEY, server_public_key.c_str(),server_public_key.length());

	std::this_thread::sleep_for(std::chrono::seconds(5));
	socket.connect("tcp://0.0.0.0:5555");
	socket.setsockopt(ZMQ_SUBSCRIBE, "", 0);

	std::cout << "Connected" << std::endl;
	while (true)
	{
		zmq::message_t message;
		socket.recv(&message,0);
		std::string received_message(static_cast<char *>(message.data()), message.size());
		std::cout << "Received: " << received_message << std::endl;
	}

	return 0;
}
