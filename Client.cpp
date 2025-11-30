#include <iostream>
#include <conio.h>

#include "Client.h"

Client::Client(std::string _address, std::string _port, std::string _target_address, asio::io_context& ioc): stream(ioc), resolver(ioc){
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

void Client::SetConnection() {
	// Initializing necessary variables //

	const auto host = resolver.resolve(address,port);

	// Connecting to the received point //

	asio::connect(stream, host.begin(), host.end());
}

std::string Client::SendRequest() {
	// Creating http request //

	beast::flat_buffer buff;
	http::request<http::string_body> req{ http::verb::get, target_address, /* Http version */ 11 };

	req.set(http::field::host, address);
	req.set(http::field::user_agent, beast::string_view{ BOOST_BEAST_VERSION_STRING });

	beast::error_code ec;
	http::write(stream, req,ec);
	if (ec) {
		std::cout << "write error: " << ec.message() << std::endl;
		exit(-1);
	}

	http::response<http::dynamic_body> res;

	http::read(stream, buff, res, ec);
	if (ec) {
		std::cout << "read error: " << ec.message() << std::endl;
		exit(-1);
	}
	std::string response_json = beast::buffers_to_string(res.body().data());

	return response_json;
}

void Client::loopRequests(std::function<void(std::string&)> parse)
{
	while (true) {
		std::string json = SendRequest();
		parse(json);
	}
}

void Client::parseJson(std::string& string_json) {
	boost::json::value json = boost::json::parse(string_json);
	std::cout << json << std::endl;
	Sleep(2000);
}