/*************************************************************
 * Name: Boyang Yan
 * Email Address: boyyan@microsoft.com
 * Last modification: 17/07/2020
 * Function: Main
 ************************************************************/

#include <iostream>
#include <thread>
#include <map>
//#include "TCPclient.h"
#include "postJSON.h"
#include "main.h"
#include "rotator.h"

using namespace std;

int main(int argc, const char *argv[]){

	cout << HEADER << endl;

	cout << "--- Rotator ---" << endl;

	rotatorManagement * rotator = new rotatorManagement("192.168.1.130", 60021);	
	std::thread tw1 = rotator->callHeartBeat();
	std::thread tw2 = rotator->callProessMoveLocationQueue();

	bool clockwise = true;
	for (int elevation = 85; elevation > 0; elevation -= 5)
	{
		if (clockwise == true){
			for (int m = 0; m < 360; m += 10)
			{
				//cout << m << " " << elevation << endl;
				rotator->wrirteToMoveLocationQueue(m, elevation);//arg one azimuth, arg two elevation
			}
			clockwise = false;
		}
		else
		{
			for (int n = 360; n > 0; n -= 10)
			{
				//cout << n << " " << elevation << endl;
				rotator->wrirteToMoveLocationQueue(n, elevation);//arg one azimuth, arg two elevation
			}
			clockwise = true;
			
		}
		
	}
	
	//rotator->wrirteToMoveLocationQueue(10, 41);
	//rotator->wrirteToMoveLocationQueue(200, 80);

	tw1.join();
	tw2.join();

	delete rotator;
	/*
	cout << "--- TCP Client ---" << endl;
	string returnMSG = "";
	TCPclient client("192.168.1.130", 60021);

	for (int i = 0; i < 1; i++){
		if (client.getSuccessStatus() == true){
			returnMSG = client.sendMSG("C2\r\n");
			cout << "return MSG: " << returnMSG << endl;
		}
		if (client.getSuccessStatus() == true){
			returnMSG = client.sendMSG("C\r\n");
			cout << "return MSG: " << returnMSG << endl;
		}
		if (client.getSuccessStatus() == true){
			returnMSG = client.sendMSG("B\r\n");
			cout << "return MSG: " << returnMSG << endl;
		}



	}*/

	/*
	cout << "--- HTTP POST JSON ---" << endl;

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

	for (int i = 0; i < 1; i++){
		// ip , port, pathOne, pathTwo, jsonData
		httpPOSTjson postJson("192.168.1.3", "9000", "api", "receiver", jsonData);
		bool success =postJson.post();
	}*/

    return 0;
}
