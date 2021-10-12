/*************************************************************
 * Name: Chujun Dong
 * Email Address: Chujun.Dong@microsoft.com
 * Last modification: 24/07/2020
 * Function: Rotator Management
 ************************************************************/

#include "rotator.h"

rotatorManagement::rotatorManagement(){
	connector_client = new TCPclient("192.168.1.130", 60021);

	currentLocation = new location;
	clearQueue(moveLocationQueue);

	initRotatorRange();

}

rotatorManagement::rotatorManagement(std::string ip, int port){
	this->port = port;
	this->IP = ip;
	connector_client = new TCPclient(ip, port);

	currentLocation = new location;
	clearQueue(moveLocationQueue);

	initRotatorRange();
	
}
void rotatorManagement::clearQueue(std::queue<location>& q) {
	std::queue<location> empty;
	swap(empty, q);
	return;
}
rotatorManagement::~rotatorManagement(){

	if(NULL != connector_client)
		delete connector_client;
	
	delete currentLocation;        
}
void rotatorManagement::wrirteToMoveLocationQueue(int azimuth, int elevation){
	location insertData;
	insertData.azimuth = azimuth;
	insertData.elevation = elevation;

	moveLocationQueue.push(insertData);

	return;
}
void rotatorManagement::initRotatorRange(){
	std::string input = "\0";
	std::cout << "Do you want to init your rotator range? (Yes/no) ";
	std::cin >> input;
	if (input == "Yes" || input == "yes"){
		//reset();
		std::cout << "Please adjust both direction to 0 degree, please press OK after finishing the operation " << std::endl;
		std::cin >> input;
		if (input == "OK"){
			initElevationZeroAndAzimuthZero();
			input = "\0";
		}
			
		std::cout << "Please adjust Elevation to 90 degree and Azimuth to 360, please press OK after finishing the operation " << std::endl;
		std::cin >> input;
		if (input == "OK")
			initElevationMaxAndAzimuthMax();
	}
	
	return;
}

bool rotatorManagement::moveDown(){

	if(NULL != connector_client){
		if (connector_client->getSuccessStatus() == true){
			std::string returnMSG = "";
			returnMSG = connector_client->sendMSG(TURN_DOWN);
			std::cout << "return MSG: " << returnMSG << std::endl;
		}
	}  

	return true;
}

bool rotatorManagement::moveUp(){

	if(NULL != connector_client){
		if (connector_client->getSuccessStatus() == true){
			std::string returnMSG = "";
			returnMSG = connector_client->sendMSG(TURN_UP);
			std::cout << "return MSG: " << returnMSG << std::endl;
		}
	}  

	return true;
}

bool rotatorManagement::moveLeft(){

	if(NULL != connector_client){
		if (connector_client->getSuccessStatus() == true){
			std::string returnMSG = "";
			returnMSG = connector_client->sendMSG(TURN_LEFT);
			std::cout << "return MSG: " << returnMSG << std::endl;
		}
	}  
	return true;
}

bool rotatorManagement::moveRight(){

	if(NULL != connector_client){
		if (connector_client->getSuccessStatus() == true){
			std::string returnMSG = "";
			returnMSG = connector_client->sendMSG(TURN_RIGHT);
			std::cout << "return MSG: " << returnMSG << std::endl;
		}
	}  
	return true;
}

int rotatorManagement::getElevation() const{
	if(NULL != connector_client){
		if (connector_client->getSuccessStatus() == true){

			std::string returnMSG = "";
			returnMSG = connector_client->sendMSG(GET_ELEVATION_ANGLE);
			std::cout << "return MSG: " << returnMSG << std::endl;

			return getreadingValue(returnMSG);
		}
	}  
	return INVALID;
}

int rotatorManagement::getAzimuth() const{
	if(NULL != connector_client){
		if (connector_client->getSuccessStatus() == true){
			std::string returnMSG = "";
			returnMSG = connector_client->sendMSG(GET_HORIZONTAL_ANGLE);
			std::cout << "return MSG: " << returnMSG << std::endl;

			return getreadingValue(returnMSG);
		}
	}  
	return INVALID;
}

void rotatorManagement::getElevationAndAzimuth(){

		if(NULL != connector_client){
			if (connector_client->getSuccessStatus() == true){
				std::string returnMSG = "";
				returnMSG = connector_client->sendMSG(GET_BOTH_ANGLE);
				std::cout << "C2 return MSG: " << returnMSG << std::endl;
				
				if (returnMSG[0] == 'A' && returnMSG[1] == 'Z' && returnMSG[2] == '=' && returnMSG[8] == 'E' && returnMSG[9] == 'L' && returnMSG[10] == '='){
					std::string azimuth = returnMSG.substr(3,1) + returnMSG.substr(4,1) + returnMSG.substr(5,1);
					std::string elevation = returnMSG.substr(11,1) + returnMSG.substr(12,1) + returnMSG.substr(13,1);

					int azimuthInt = std::stoi (azimuth, nullptr, 10);
					int elevationInt = std::stoi (elevation, nullptr, 10);

					if(azimuthInt < 0 && azimuthInt >360)
						return;
					if(elevationInt < 0 && elevationInt > 90)
						return;

					currentLocation->azimuth = azimuthInt;
					currentLocation->elevation = elevationInt;

				}
			}
		} 


	return;
}

std::vector<std::string> rotatorManagement::splitReadings(std::string readings) const
{
    std::string delimiter_middle = "  ";
    std::string AZ = readings.substr(0,readings.find(delimiter_middle));
    std::string EL = readings.substr(readings.find(delimiter_middle) + 2 , readings.length());
    std::vector<std::string> test; // Empty on creation
    test.push_back(AZ); // Adds an element
    test.push_back(EL);
    return test;
}

int rotatorManagement::getreadingValue(std::string reading) const{

	std::string delimiter = "=";
	std::string token = reading.substr(reading.find(delimiter) + 1, reading.length());

	return stoi(token);
}

bool rotatorManagement::setElevationStop(){

	if(NULL != connector_client){
		if (connector_client->getSuccessStatus() == true){
			std::string returnMSG = "";
			returnMSG = connector_client->sendMSG(HORIZONTAL_STOP);
			std::cout << "return MSG: " << returnMSG << std::endl;
		}
	}  
	return true;
}

bool rotatorManagement::setAzimuthStop(){

	if(NULL != connector_client){
		if (connector_client->getSuccessStatus() == true){
			std::string returnMSG = "";
			returnMSG = connector_client->sendMSG(ELEVATION_STOP);
			std::cout << "return MSG: " << returnMSG << std::endl;
		}
	}  
	return true;
}
bool rotatorManagement::setElevationAndAzimuthStop(){

	if(NULL != connector_client){
		if (connector_client->getSuccessStatus() == true){
			std::string returnMSG = "";
			returnMSG = connector_client->sendMSG(STOP_BOTH_DIRE);
			std::cout << "return MSG: " << returnMSG << std::endl;
		}
	}  
	return true;
}

bool rotatorManagement::setSpeedLevel(speed_level speed){

	std::string cmd = "";

	switch (speed)
	{
		case low: cmd = LOW_SPEED;
			break;
		case mediumLow: cmd = MEDIUM_LOW_SPEED;
			break;
		case mediumHigh: cmd = MEDIUM_HIGH_SPEED;
			break;
		case high: cmd = HIGH_SPEED;
			break;
	
		default:
			cmd = LOW_SPEED;
			break;
	}
	if(NULL != connector_client){
		if (connector_client->getSuccessStatus() == true){
			std::string returnMSG = "";
			returnMSG = connector_client->sendMSG(cmd);
			std::cout << "return MSG: " << returnMSG << std::endl;
		}
	}  
	return true;
}

bool rotatorManagement::initElevationZeroAndAzimuthZero(){

	if(NULL != connector_client){
		if (connector_client->getSuccessStatus() == true){
			std::string returnMSG = "";
			std::cout << "begin INIT_AZUMUTH_ANGLE_ZERO" << std::endl;
			returnMSG = connector_client->sendMSG(INIT_AZUMUTH_ANGLE_ZERO);
			std::cout << "initElevationZeroAndAzimuthZero return MSG: " << returnMSG << std::endl;

			std::cout << "begin INIT_ELEVATION_ANGLE_ZERO" << std::endl;
			returnMSG = connector_client->sendMSG(INIT_ELEVATION_ANGLE_ZERO);
			std::cout << "INIT_ELEVATION_ANGLE_ZERO return MSG: " << returnMSG << std::endl;
		}
    }

	return true;
}

bool rotatorManagement::initElevationMaxAndAzimuthMax(){
	
	if(NULL != connector_client){
		if (connector_client->getSuccessStatus() == true){
			std::string returnMSG = "";
			
			std::cout << "begin INIT_AZUMUTH_ANGLE_MAX" << std::endl;
			returnMSG = connector_client->sendMSG(INIT_AZUMUTH_ANGLE_MAX);
			std::cout << "INIT_AZUMUTH_ANGLE_MAX return MSG: " << returnMSG << std::endl;

			std::cout << "begin INIT_ELEVATION_ANGLE_MAX" << std::endl;
			returnMSG = connector_client->sendMSG(INIT_ELEVATION_ANGLE_MAX);
			std::cout << "INIT_ELEVATION_ANGLE_MAX return MSG: " << returnMSG << std::endl;
		}
    }  
	return true;
}

bool rotatorManagement::reset(){
	std::cout << "reset" << std::endl;

	if(NULL != connector_client)
	{
		if (connector_client->getSuccessStatus() == true)
		{
			std::string returnMSG = "";
			returnMSG = connector_client->sendMSG(RESET);
			std::cout << "RESET: " << RESET << std::endl;
			std::cout << "return MSG: " << returnMSG << std::endl;
		}
	}
	return true;
	
}

bool rotatorManagement::printVersion()
{

}

bool rotatorManagement::setElevationAndAzimuth(int x, int y){
	if(x < 0 || x > 360)
		return false;
	if(y < 0 || y > 90)
		return false;	

	if(NULL != connector_client){
		if (connector_client->getSuccessStatus() == true){
			std::string returnMSG = "";
			std::cout << "setElevationAndAzimuth send MSG: " << "W" + angleToString(x) + " " + angleToString(y) + "\r\n" << std::endl;
			connector_client->onlySendMSG("W" + angleToString(x) + " " + angleToString(y) + "\r\n");
			//std::cout << "setElevationAndAzimuth return MSG: " << returnMSG << std::endl;
		}
    }  
	return true;

}
bool rotatorManagement::setElevation(int angle){
	if (angle > 360 && angle < 0){
		return false;
	}
	
	if(NULL != connector_client){
		if (connector_client->getSuccessStatus() == true){
			std::string returnMSG = "";
			returnMSG = connector_client->sendMSG("M" + angleToString(angle) + "\r\n");
			std::cout << "return MSG: " << returnMSG << std::endl;
		}
    }  
	return true;
}

std::string rotatorManagement::angleToString(int angle){
	std::stringstream ss;
	ss << std::setw(3) << std::setfill('0') << angle;
	return ss.str();
}

void rotatorManagement::heartBeat(){
	std::cout << "heart beat start" << std::endl;

	while(true){
		getElevationAndAzimuth();
		cv.notify_all();
		//std::vector<int> readings = getElevationAndAzimuth();
		std::cout << "heartBeat called" << std::endl;

		std::this_thread::sleep_for(std::chrono::milliseconds(200));

	}
	
	return;
}

std::thread rotatorManagement::callHeartBeat(){
	return std::thread([=] { heartBeat(); });
};

std::thread rotatorManagement::callProessMoveLocationQueue(){
	return std::thread([=] { proessMoveLocationQueue(); });
};
void rotatorManagement::proessMoveLocationQueue(){
	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		int setAzimuth = 0;
		int setElevation = 0;
		if (!moveLocationQueue.empty()) {

			std::unique_lock<std::mutex> lk(cv_m);

			bool ok = setElevationAndAzimuth(moveLocationQueue.front().azimuth, moveLocationQueue.front().elevation);

    		cv.wait(lk, [this]{return ((this->currentLocation->azimuth >= moveLocationQueue.front().azimuth - 2) && (currentLocation->azimuth <= moveLocationQueue.front().azimuth + 2))
					  && ((currentLocation->elevation >= moveLocationQueue.front().elevation - 2) && (currentLocation->elevation <= moveLocationQueue.front().elevation + 2));});

			moveLocationQueue.pop();
		}
		
	}
	
	return;
}