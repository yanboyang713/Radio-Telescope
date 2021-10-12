#include "postJSON.h"

using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams

//Other important namespaces not used in this tutorial in Casablanca include:
using namespace web::http::experimental::listener;          // HTTP server
using namespace web::experimental::web_sockets::client;     // WebSockets client
using namespace web::json;                                  // JSON library

httpPOSTjson::httpPOSTjson(){

	this->data.IP = "";
	this->data.port = "";
	this->data.pathOne = "";
	this->data.pathTwo = "";
	this->data.jsonData;

}

httpPOSTjson::httpPOSTjson(std::string IP, std::string port, std::string pathOne, std::string pathTwo, std::map<std::string, std::string> jsonData){

	this->data.IP = IP;
	this->data.port = port;
	this->data.pathOne = pathOne;
	this->data.pathTwo = pathTwo;
	this->data.jsonData = jsonData;

}

httpPOSTjson::~httpPOSTjson(){

	this->data.IP = "";
	this->data.port = "";
	this->data.pathOne = "";
	this->data.pathTwo = "";
	this->data.jsonData;

}

bool httpPOSTjson::post()
{

	dataType Data = this->data;
	// Create user data as JSON object and make POST request.
	auto postJson = pplx::create_task([Data]() {
		json::value jsonObject;
	for(auto it = Data.jsonData.cbegin(); it != Data.jsonData.cend(); ++it){
		std::cout << it->first << " " << it->second << "\n";
		jsonObject[U(it->first)] = json::value::string(U(it->second));
	}

	return http_client(U("http://" + Data.IP + ":" + Data.port))
		.request(methods::POST,
		uri_builder(U(Data.pathOne)).append_path(U(Data.pathTwo)).to_string(),
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
