#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <conio.h>

#include "Handler.h"
#include "DataManager.h"

Handler::Handler(std::string _address, std::string _port, std::string _target_address, asio::io_context& ioc): stream(ioc), resolver(ioc){
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



void Handler::SetConnection() {
	// Initializing necessary variables //

	const auto host = resolver.resolve(address,port);

	// Connecting to the received point //
	
	asio::connect(stream, host.begin(), host.end());
	
}



std::string Handler::SendRequest() {
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



void Handler::parseJson(std::string& string_json) {
	boost::json::value json = boost::json::parse(string_json);

	const auto& main_obj = json.get_object();

	if (main_obj.at("currentcount").as_int64() == 0) {
		Sleep(2000);
		return;
	}

	const auto& time_boost_str = main_obj.at("timestamp").get_int64();
	std::cout << convertTime(time_boost_str) << std::endl;

	//const auto& players = main_obj.at("players").get_array();

	/*for (const auto& player : players) {
		std::cout << "\nName: " << player.at("name").as_string() << std::endl;
		std::cout << "World: " << player.at("world").as_string() << std::endl;
		std::cout << "X: " << player.at("x").as_double() << std::endl;
		std::cout << "Y: " << player.at("y").as_double() << std::endl;
		std::cout << "Z: " << player.at("z").as_double() << std::endl;
		std::cout << "Hp: " << player.at("health").as_double() << std::endl;
	}*/

	Sleep(2000);
}



std::string Handler::convertTime(const unsigned long long time) {

	std::time_t temp = time / 1000; // Division by 1000 is necessary to remove milliseconds
	std::tm t;
	gmtime_s(&t, &temp);
	std::stringstream ss;
	ss << std::put_time(&t, "%Y-%m-%d %I:%M:%S %p");
	return ss.str();
}
