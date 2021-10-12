/*************************************************************
 * Name: Boyang Yan
 * Email Address: boyyan@microsoft.com
 * Last modification: 17/07/2020
 * Function: TCP Client
 ************************************************************/

#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <iostream>

class TCPclient{

	private:
		int valread;
		int sock;
		struct sockaddr_in serv_addr;
		std::string IP;
		uint16_t port;
		bool successStatus;
		char *message;

		void read_message();
		std::string convertToString(char*, int);
	public:
		TCPclient();
		TCPclient(std::string, int);
		~TCPclient();

		std::string sendMSG(std::string);
		void onlySendMSG(std::string);
		bool getSuccessStatus() const;
		bool init();

};

#endif //TCP_CLIENT_H
