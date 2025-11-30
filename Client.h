#pragma once
#include <string>
#include "boost/asio/ip/tcp.hpp"
#include "boost/beast/core.hpp"
#include "boost/beast/http.hpp"
#include "boost/asio/connect.hpp"
#include "boost/beast/version.hpp"
#include "boost/json.hpp"

namespace beast = boost::beast;
namespace asio = boost::asio;
namespace http = boost::beast::http;
using tcp = asio::ip::tcp;

class Client {
private:
	std::string port;
	std::string address;
	std::string target_address; // Address after '/'. For example: "google.com/test", "test" is a target address //
	tcp::socket stream;
	tcp::resolver resolver;

	void confirmAction();

public:
	Client(std::string _address, std::string _port, std::string _target_address, asio::io_context& ioc);
	std::string SendRequest();
	void parseJson(std::string& string_json);
	void loopRequests(std::function<void(std::string&)> parse);
	void SetConnection();
};
