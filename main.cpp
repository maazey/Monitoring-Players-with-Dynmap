#define CURL_STATICLIB

#include <curl.h>
#include <iostream>

#include "Client.h"

int main() {
	asio::io_context ioc;
	Client client{ "88.151.117.86", "25783", "/up/world/world/", ioc};;
	client.SetConnection();

	auto lambda_parse = [&](std::string& json) {client.parseJson(json); };
	client.loopRequests(lambda_parse);

	if (1 == 1) {
		std::cout << "qwe" << std::endl;
	}
	else {
		std::cout << "qwe" << std::endl;
	}
}