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

using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams

//Other important namespaces not used in this tutorial in Casablanca include:
using namespace web::http::experimental::listener;          // HTTP server
using namespace web::experimental::web_sockets::client;     // WebSockets client
using namespace web::json;                                  // JSON library

bool post(std::map<std::string, std::string>);

int main(int argc, char const *argv[])
{
    std::cout << "Hello, This is a Test for REST API" << std::endl;

    std::map<std::string, std::string> jsonData;

    jsonData["timestamp"] = "0000000";
    jsonData["gps"] = "0000000";
    jsonData["rawData"] = "0000000";
    jsonData["elevation"] = "0000000";
    jsonData["azimuth"] = "0000000";
    jsonData["centerFrequency"] = "0000000";
    jsonData["bandwidth"] = "0000000";
    jsonData["totalSamplingPoints"] = "0000000";
    jsonData["samplingDepth"] = "0000000";

   
    for (int i = 0; i < 10; i++){
	    bool success = post(jsonData);
    }

    return 0;
}

bool post(std::map<std::string, std::string> jsonData)
{

	// Create user data as JSON object and make POST request.
	auto postJson = pplx::create_task([jsonData]() {
		json::value jsonObject;
	for(auto it = jsonData.cbegin(); it != jsonData.cend(); ++it){
		std::cout << it->first << " " << it->second << "\n";
		jsonObject[U(it->first)] = json::value::string(U(it->second));
	}

	return http_client(U("http://192.168.1.3:8000"))
		.request(methods::POST,
		uri_builder(U("api")).append_path(U("receiver")).to_string(),
		jsonObject.serialize(), U("application/json"));
	})

	// Get the response.
	.then([](http_response response) {
		// Check the status code.
		printf("Received response status code:%u\n\n\n", response.status_code());
		if (response.status_code() != 200) {
			throw std::runtime_error("Returned " + std::to_string(response.status_code()));
		}

		// Convert the response body to JSON object.
		return response.status_code();
	});
    // Wait for all the outstanding I/O to complete and handle any exceptions
    try
    {
        postJson.wait();
    }
    catch (const std::exception &e)
    {
        printf("Error exception:%s\n", e.what());
	return false;
    }

    return true;
}
