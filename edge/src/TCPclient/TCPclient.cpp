/*************************************************************
 * Name: Boyang Yan
 * Email Address: boyyan@microsoft.com
 * Last modification: 17/07/2020
 * Function: TCP Client
 ************************************************************/

#include "TCPclient.h"

TCPclient::TCPclient(){
	valread = 0;
        sock = 0;
	IP = "127.0.0.1";
	port = 8080;
	successStatus = false;
	message = NULL;

	serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(8080);
	
	successStatus = init();

}

TCPclient::TCPclient(std::string IP, int port){

	valread = 0;
        sock = 0;
	successStatus = false;
	this->IP = IP;
	this->port = port;
	message = NULL;

	serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(port);

	successStatus = init();
}

TCPclient::~TCPclient(){


}
bool TCPclient::getSuccessStatus() const{
	return successStatus;
}

bool TCPclient::init(){
	/*
         * sockfd = socket(domain, type, protocol)
         * sockfd: socket descriptor, an integer (like a file-handle)
         * domain: integer, communication domain e.g., AF_INET (IPv4 protocol) , AF_INET6 (IPv6 protocol)
         * type: communication type SOCK_STREAM: TCP(reliable, connection oriented) SOCK_DGRAM: UDP(unreliable, connectionless)
         * protocol: Protocol value for Internet Protocol(IP), which is 0. This is the same number which appears on protocol field in the IP header of a packet.(man protocols for more details)
         */

        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
                printf("\n Socket creation error \n");
                return false;
        }

        // Convert IPv4 and IPv6 addresses from text to binary form
        if(inet_pton(AF_INET, IP.c_str(), &serv_addr.sin_addr)<=0){
                printf("\nInvalid address/ Address not supported \n");
                return false;
        }

        if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
                printf("\nConnection Failed \n");
                return false;
        }

	return true;
}
std::string TCPclient::sendMSG(std::string msg){

	char Buffer[1024] = {0};
        send(sock , msg.c_str() , msg.length() , 0 );
        //printf("message sent success\n");

        valread = read( sock , Buffer, 1024);

	return convertToString(Buffer, 1024);

}

void TCPclient::onlySendMSG(std::string msg){
	char Buffer[1024] = {0};
    send(sock , msg.c_str() , msg.length() , 0 );
    //printf("message sent success\n");
	return;
}

void TCPclient::read_message() {

	char data;
	ssize_t data_read;

	while ((data_read = recv(sock, &data, 1, 0)) > 0 && data != '\0')
		*message++ = data;

	if (data_read == -1) {
		perror("CLIENT: ERROR recv()");
		exit(EXIT_FAILURE);
	}

	*message = '\0';

	std::cout << message << std::endl;

	return;
}

// converts character array 
// to string and returns it 
std::string TCPclient::convertToString(char* array, int size) 
{ 
	std::string stringReturn = ""; 
	for (int i = 0; i < size; i++) { 
		stringReturn = stringReturn + array[i]; 
	} 
	return stringReturn; 
} 
