#ifndef RIDER_H
#define RIDER_H

#include <iostream>
using namespace std;

class Rider {
public:
	string username;
	string password;
	int uniqueId;
	double locY, locX;
	Rider();
	Rider(string,string, int);
	Rider(string,string, int, double, double);
	void setLoc(double, double);
	double getLocY();
	double getLocX();
};

#endif
