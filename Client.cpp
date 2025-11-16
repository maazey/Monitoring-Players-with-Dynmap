#include <iostream>

#include "Client.h"

Client::Client(std::string _address, std::string _port, std::string _target_address) {
	if (!_address.empty()) {
		address = _address;
	}
	if (!_port.empty()) {
		port = _port;
	}
	if (!_target_address.empty()) {
		target_address = _target_address;
	}
	
}

void Client::setConnection() {
	// Initializing necessary variables //
	asio::io_context ioc;
	tcp::resolver resolver{ ioc };
	tcp::socket stream{ ioc };
	const auto host = resolver.resolve(address,port);

	// Connecting to the received point //

	asio::connect(stream, host.begin(), host.end());

	// Creating http request //

	http::request<http::string_body> req{ http::verb::get, target_address, 11 };
	req.set(http::field::host, address);
	req.set(http::field::user_agent, beast::string_view{ BOOST_BEAST_VERSION_STRING });

	http::write(stream, req);

	beast::flat_buffer buff;
	http::response<http::string_body> res;

	http::read(stream, buff, res);
	std::cout << res.body() << std::endl;
	

}