#include "rider.h"

Rider::Rider() {};

Rider::Rider(string USERNAME, string PASSWORD, int UNIQUEID) {
	username = USERNAME;password = PASSWORD;uniqueId = UNIQUEID;
};
Rider::Rider(string USERNAME, string PASSWORD, int UNIQUEID, double LOCX, double LOCY) {
	username = USERNAME;password = PASSWORD;uniqueId = UNIQUEID;
	locY = LOCY; locX = LOCX;
};

void Rider::setLoc(double x, double y) {
	locX = x; locY = y;
}
double Rider::getLocY() {
	return locX;
}
double Rider::getLocX() {
	return locX;
}