#define CURL_STATICLIB
#include <curl.h>
#include "char.h"
#include <iostream>
//#include <boost/>

int main() {
	CURL* curl;
	CURLcode result;
	curl = curl_easy_init();
	if (curl == 0) {
		std::cerr << "curl didn't initialize" << std::endl;
		return -1;
	}
	
	while (true) {
		char address[64] = "http://88.151.117.86:25783/up/world/DIM1/";
		curl_easy_setopt(curl, CURLOPT_URL, address);
		printc(&address[0],"GET request to ");

		result = curl_easy_perform(curl);
		
		if (result != CURLE_OK) {
			std::cerr << "curl error: " << curl_easy_strerror(result) << std::endl;
			return -1;
		}
		Sleep(2000);
	}
	curl_easy_cleanup(curl);
}	
