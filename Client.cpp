#include "Client.h"
#include "boost/beast.hpp"
#include "boost/asio/connect.hpp"
#include "boost/asio/ip/tcp.hpp"
#include <iostream>

Client::Client(std::string _address) {
	if (!_address.empty()) {
		address = _address;
	}
	else {
		std::cerr << "address can't be empty!" << std::endl;
	}
}

//std::string Client::getResponse() {
//	namespace asio = boost::asio;
//	
//
//}