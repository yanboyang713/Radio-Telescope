/*************************************************************
 * Name: Boyang Yan
 * Email Address: boyyan@microsoft.com
 * Last modification: 18/07/2020
 * Function: HTTP POST JSON 
 ************************************************************/
#ifndef HTTP_POST_JSON_H
#define HTTP_POST_JSON_H

#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <iostream>
#include <map>
#include <typeinfo>

//Here is a list of other important header files in Casablanca, but we won't be using them in this example:
#include <cpprest/http_listener.h>              // HTTP server
#include <cpprest/json.h>                       // JSON library
#include <cpprest/uri.h>                        // URI library
#include <cpprest/ws_client.h>                  // WebSocket client
#include <cpprest/containerstream.h>            // Async streams backed by STL containers
#include <cpprest/interopstream.h>              // Bridges for integrating Async streams with STL and WinRT streams
#include <cpprest/rawptrstream.h>               // Async streams backed by raw pointer to memory
#include <cpprest/producerconsumerstream.h>     // Async streams for producer consumer scenarios

class httpPOSTjson{

	private:

		struct dataType
		{
			std::string IP;
			std::string port;
			std::string pathOne;
			std::string pathTwo;
			std::map<std::string, std::string> jsonData;
		} data;
	
		

	public:
		httpPOSTjson();
		httpPOSTjson(std::string, std::string, std::string, std::string, std::map<std::string, std::string>);
		~httpPOSTjson();
		bool post();

};

#endif //HTTP_POST_JSON_H