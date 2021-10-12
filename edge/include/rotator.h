/*************************************************************
 * Name: Chujun Dong
 * Email Address: Chujun.Dong@microsoft.com
 * Last modification: 24/07/2020
 * Function: Rotator Management
 ************************************************************/
#ifndef ROTATOR_MANAGEMENT_H
#define ROTATOR_MANAGEMENT_H

#include <string>
#include <iostream>
#include <vector>
#include <thread>
#include <condition_variable>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <queue>
#include <deque>
#include <regex>
#include "TCPclient.h"

#define GET_ELEVATION_ANGLE "C" "\r\n"
#define GET_HORIZONTAL_ANGLE "B" "\r\n"
#define TURN_LEFT "L" "\r\n"
#define TURN_RIGHT "R" "\r\n"
#define TURN_UP "U" "\r\n"
#define TURN_DOWN "D" "\r\n"
#define ELEVATION_STOP "A" "\r\n"
#define HORIZONTAL_STOP "E" "\r\n"
#define STOP_BOTH_DIRE "S" "\r\n"
#define INIT_AZUMUTH_ANGLE_ZERO "O" "\r\n" //0 degree
#define INIT_AZUMUTH_ANGLE_MAX "F" "\r\n" //360 degree
#define LOW_SPEED "X1" "\r\n"
#define MEDIUM_LOW_SPEED "X2" "\r\n"
#define MEDIUM_HIGH_SPEED "X3" "\r\n"
#define HIGH_SPEED "X4" "\r\n"
#define GET_BOTH_ANGLE "C2" "\r\n"
#define INIT_ELEVATION_ANGLE_ZERO "O2" "\r\n" //0 degree
#define INIT_ELEVATION_ANGLE_MAX "F2" "\r\n" //90 degree
#define RESET "RST" "\r\n"
#define SET_ELEVATION_ANGLE(x) "M" x "\r\n"
#define SET_BOTH_ANGLE(x,y) "W" x y "\r\n"

#define INVALID -1

enum speed_level {low=0, mediumLow, mediumHigh, high};

struct location {
	int elevation;
	int azimuth;
};

class rotatorManagement{
	private:
		std::string port;
		std::string IP;
		TCPclient * connector_client;
		
		location * currentLocation;
		std::queue<location> moveLocationQueue;

		std::condition_variable cv;
		std::mutex cv_m;

		void clearQueue(std::queue<location>&);
		int getreadingValue(std::string) const;
	
		std::vector<std::string> splitReadings(std::string) const;

		void heartBeat();
		void proessMoveLocationQueue();

		std::string angleToString(int);

	public:
		rotatorManagement();
		rotatorManagement(std::string ip, int port);
		~rotatorManagement();
		
		std::thread callHeartBeat();
		std::thread callProessMoveLocationQueue();

		void wrirteToMoveLocationQueue(int, int);

		void initRotatorRange();

		bool moveDown();
		bool moveUp();

		bool moveLeft();
		bool moveRight();

		int getElevation() const;
		int getAzimuth() const;
		//std::vector<int> getElevationAndAzimuth() const;
		void getElevationAndAzimuth();

		bool setElevationStop();
		bool setAzimuthStop();
		bool setElevationAndAzimuthStop();

		bool setSpeedLevel(speed_level speed);

		bool initElevationZeroAndAzimuthZero();
		bool initElevationMaxAndAzimuthMax();

		bool reset();
		bool printVersion();

		bool setElevationAndAzimuth(int, int);
		bool setElevation(int);
};

#endif //ROTATOR_MANAGEMENT_H
