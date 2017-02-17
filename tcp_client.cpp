// tcp_client.cpp 

#include <iostream>
#include <thread>
#include <boost/asio.hpp>
#include <boost/array.hpp>

namespace asio = boost::asio;

int main(int argc, char* argv[]) {
	asio::io_service io_service;
	asio::ip::tcp::socket socket(io_service);

	socket.connect(asio::ip::tcp::endpoint(asio::ip::address::from_string("127.0.0.1"), 60000));


	while(1) {
		boost::array<char, 128> buf;
		boost::system::error_code error;

		size_t len = socket.read_some(boost::asio::buffer(buf), error);
		std::cout.write(buf.data(), len);
	}

}
