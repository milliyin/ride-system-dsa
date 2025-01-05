#include "driver.h"

Driver::Driver() {}

Driver::Driver(string USERNAME,string PASSWORD, int UNIQUEID) {
	username = USERNAME;password = PASSWORD;uniqueId = UNIQUEID;
};
Driver::Driver(string USERNAME, string PASSWORD, int UNIQUEID, double LOCX, double LOCY) {
	username = USERNAME;password = PASSWORD;uniqueId = UNIQUEID;
	locY = LOCY; locX = LOCX;
};
Driver::Driver(string USERNAME, string PASSWORD, int UNIQUEID, double LOCX, double LOCY,bool AVAIL) {
	username = USERNAME;password = PASSWORD;uniqueId = UNIQUEID;
	locY = LOCY; locX = LOCX; availability = AVAIL;
};

void Driver::setLoc(int x, int y){
	locX = x; locY = y;
}
int Driver::getLocY(){
	return locX;
}
int Driver::getLocX(){
	return locX;
}
bool Driver::getAvil(){
	return availability;
}
void Driver::setAvil(bool x) {
	availability = x;
}