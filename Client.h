#pragma once
#include <string>
#include "boost/asio/ip/tcp.hpp"
#include "boost/beast/core.hpp"
#include "boost/beast/http.hpp"
#include "boost/asio/connect.hpp"
#include "boost/beast/version.hpp"

namespace beast = boost::beast;
namespace asio = boost::asio;
namespace http = boost::beast::http;
using tcp = asio::ip::tcp;

class Client {
	std::string port;
	std::string address;
	std::string target_address; // address after '/'. example - "google.com/test", "test" is a target address //
public:
	Client(std::string _address, std::string _port, std::string _target_address);
	void setConnection();
	
};
