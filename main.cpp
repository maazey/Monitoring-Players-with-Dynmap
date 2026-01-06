#include <iostream>

#include "Handler.h"

int main() {
	asio::io_context ioc;
	Handler handler{ "88.151.117.86", "25783", "/up/world/world/", ioc};
	handler.SetConnection();

	while (true) {
		std::string json = handler.SendRequest();
		handler.parseJson(json);
	}
}