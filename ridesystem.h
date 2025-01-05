#ifndef RIDESYSTEM_H
#define RIDESYSTEM_H

#include "driver.h";
#include "rider.h";
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <map>
#include <cmath>
#include <thread>


using namespace std;

class Ridesystem {
	private:
		map<string, Driver> RegMapD;
		map<string, Rider> RegMapR;
		double distanceCal(double, double, double, double);
		void rideinProcess(Rider*, Driver*, double);
	public:
		struct rideinfo;
		struct CompareDrivers;
	string DriverFile, RiderFile;
	vector<Driver> Drivers;
	vector<Rider> Riders;
	Rider *LogedInrider;
	int LogedinID; bool LogedinAs;
	int LastRegIdD, LastRegIdR;
	void loadDrivers();
	void saveDriver();
	void loadRider();
	void saveRider();
	Ridesystem(string,string);
	bool login(string, string);
	bool logout();
	void printAll();
	bool registion(string, string, bool,double, double);
	Driver* onlineDrivers();
	bool requestDriver();
	~Ridesystem();
};

#endif