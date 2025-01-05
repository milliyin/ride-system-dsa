#include "driver.h";
#include "rider.h";
#include <iostream>
#include "ridesystem.h";
using namespace  std;


int main() {
	Ridesystem ridesystem("G:/Dsa/open-ended-lab/open-ended-lab/Drivers.csv", "G:/Dsa/open-ended-lab/open-ended-lab/Riders.csv");
	ridesystem.registion("DriverIlliyin", "passheheh", 0, 54, 89);
	ridesystem.login("illiyin", "123"); //login as Rider
	ridesystem.logout(); //logout
	ridesystem.login("DriverIlliyin", "passheheh"); // login as Driver
	ridesystem.logout(); //logout
	ridesystem.login("000", "pass2182"); // logining in as non;

	ridesystem.login("illiyin", "123"); //login as Rider
	ridesystem.requestDriver(); //requesting the closest rider;
	ridesystem.logout(); // loging out

	ridesystem.login("Rider100", "xah0df");//login as Rider
	ridesystem.requestDriver(); //requesting the closest rider;
	ridesystem.logout(); // loging out

	while(true){}

	//cout << ridesystem.registion("illiyin","123",1,45,67.6) << endl;
}
