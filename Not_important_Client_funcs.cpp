#include <iostream>

#include "Handler.h"


void Handler::confirmAction() {
	std::cout << "\nPress \"Enter\" to continue running the program or type \"Exit\" to exit.\n";
	std::string line;
	std::getline(std::cin, line);
	std::transform(line.begin(), line.end(), line.begin(), [](char c) {
		return std::tolower(c);
		});
	std::cout << line << std::endl;
	if (line == "exit") {
		exit(1);
	}
}