#ifndef DRIVER_H
#define DRIVER_H

#include <iostream>
using namespace std;

class Driver {
public:
	string username;
	string password;
	int uniqueId;
	double locY, locX;
	bool availability;
	Driver();
	Driver(string,string, int);
	Driver(string,string, int,double, double);
	Driver(string, string, int, double, double,bool);
	void setLoc(int, int);
	int getLocY();
	int getLocX();
	bool getAvil();
	void setAvil(bool);
};

#endif