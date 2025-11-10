#pragma once
#include <string>

class Client {
	std::string address;

public:
	Client(std::string _address);
	std::string getResponse();
};
