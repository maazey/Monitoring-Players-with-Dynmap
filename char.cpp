#include "char.h"
#include <iostream>
#include <string>

void addTimeToAddress(char* c) {
	char* second = c;
	std::time_t now = std::time(0);
	std::string time_str = std::to_string(now);
	while (*second != '\0') second++;

	for (int i = 0; i < time_str.size(); ++i, ++second) {
		*second = time_str[i];
	}
	*second = '\0';
}

void printc(char* c, const std::string& arg) {
	char* main = c;
	std::cout << "\n" << arg;
	while (*main != '\0') {
		std::cout << *main;
		++main;
	}
	std::cout << "\n";
}