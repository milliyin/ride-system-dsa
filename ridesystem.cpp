#include "ridesystem.h"

void Ridesystem::loadDrivers() {
    fstream fin1;
    fin1.open(DriverFile, ios::in);
    string temp1, line;getline(fin1, temp1); int a=0;
    while (getline(fin1, line)) {
        string name, password; double id, x, y, avail;
        istringstream iss(line);
        getline(iss, name, ',');
        getline(iss, password, ',');
        iss >> id;
        iss.ignore(200, ',');
        iss >> x;
        iss.ignore(200, ',');
        iss >> y;
        iss.ignore(200, ',');
        iss >> avail;
        Drivers.push_back(Driver(name, password, id, x, y,avail));
        RegMapD[name] = Driver(name, password, id, x, y, avail); a++;
    }
    LastRegIdD = Drivers[a-1].uniqueId;
    cout << "Total Drivers Loaded:" << a << endl;
}
void Ridesystem::saveDriver() {
    fstream fout;
    fout.open(DriverFile, ios::out);
    fout << "Name,Password,Id,X,Y,Availability" << endl;
    for (int i = 0;i < Drivers.size();i++) {
        fout << Drivers[i].username << "," << Drivers[i].password << "," << Drivers[i].uniqueId << "," << Drivers[i].locX << "," 
            << Drivers[i].locY << "," << Drivers[i].availability << endl;
    }
}
void Ridesystem::loadRider() {
    fstream fin1;
    fin1.open(RiderFile, ios::in);
    string temp1, line;getline(fin1, temp1); int a=0;
    while (getline(fin1, line)) {
        string name, password; double id, x, y, avail;
        istringstream iss(line);
        getline(iss, name, ',');
        getline(iss, password, ',');
        iss >> id;
        iss.ignore(200, ',');
        iss >> x;
        iss.ignore(200, ',');
        iss >> y;
        iss.ignore(200, ',');
        iss >> avail;
        Riders.push_back(Rider(name, password, id, x, y));
        RegMapR[name] = Rider(name, password, id, x, y);
        a++;
    }
    LastRegIdR = Riders[a-1].uniqueId;
    cout << "Total Riders Loaded:" << a << endl;
}
void Ridesystem::saveRider() {
    fstream fout;
    fout.open(RiderFile, ios::out);
    fout << "Name,Password,Id,X,Y" << endl;
    for (int i = 0;i < Riders.size();i++) {
        fout << Riders[i].username << "," << Riders[i].password << "," << Riders[i].uniqueId << "," << Riders[i].locX << "," << Riders[i].locY << endl;
    }

}
Ridesystem::Ridesystem(string f1, string f2) {
    DriverFile = f1; RiderFile = f2;
    this->loadDrivers();
    this->loadRider();
}
bool Ridesystem::login(string user, string pass) {
    auto finder = RegMapD.find(user);
    if (finder != RegMapD.end()) {
        if (finder->second.password == pass) {
            LogedinID = RegMapD[user].uniqueId;
            LogedinAs = 0;
            cout << "Logined in as " << RegMapD[user].username<<endl;
            return 1;
        }
    }
    auto finder2 = RegMapR.find(user);
    if (finder2 != RegMapR.end()) {
        if (finder2->second.password == pass) {
            LogedinID = RegMapR[user].uniqueId;
            LogedInrider = &RegMapR[user];
            LogedinAs = 1;
            cout << "Logined in as " << RegMapR[user].username << endl;
            return 1;
        }
    }
    return 0;
}

void Ridesystem::printAll() {
    for (int i = 0;i < Drivers.size();i++) {
        cout << Drivers[i].username << "," << Drivers[i].password << "," << Drivers[i].uniqueId << "," << Drivers[i].locX << "," << Drivers[i].locY << "," 
            << Drivers[i].availability << endl;
    }
    for (int i = 0;i < Riders.size();i++) {
        cout << Riders[i].username << "," << Riders[i].password << "," << Riders[i].uniqueId << "," << Riders[i].locX << "," << Riders[i].locY << endl;
    }
}
bool Ridesystem::logout() {
        
    LogedinID = NULL;
    LogedinAs = NULL;
    cout << "Logging Out.." << endl;
    return 1;
}
bool Ridesystem::registion(string name, string pass, bool pick,double x,double y) {
    if (pick) {
        Riders.push_back(Rider(name, pass, LastRegIdR+1, x, y));
        RegMapR[name] = Rider(name, pass, LastRegIdR + 1, x, y);
        LastRegIdR = LastRegIdR + 1;
        return 1;
    }
    else {
        Drivers.push_back(Driver(name, pass, LastRegIdD + 1, x, y, 1));
        RegMapD[name] = Driver(name, pass, LastRegIdD + 1, x, y, 1);
        LastRegIdD = LastRegIdD + 1;
        return 1;
    }
    return 0;
}
double Ridesystem::distanceCal(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

struct Ridesystem::CompareDrivers {
    double userX, userY;
    CompareDrivers(double x, double y):userX(x),userY(y){}
    double distanceCal(double x1, double y1, double x2, double y2) {
        return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
    }
    bool operator()(Driver& d1, Driver d2) {
        double dis1 = distanceCal(userX, userY, d1.locX, d1.locY);
        double dis2 = distanceCal(userX, userY, d2.locX, d2.locY);
        return dis1 > dis2;
    }
};

struct Ridesystem::rideinfo {
    Driver* driver;int time;
};

Driver* Ridesystem::onlineDrivers() {
    if (LogedinAs) {
        Driver* r1 = NULL;
        priority_queue<Driver, vector<Driver>, CompareDrivers> onlineDriversQueue(CompareDrivers(LogedInrider->locX, LogedInrider->locY));
        for (int i = 0;i < Drivers.size();i++) {
            if (Drivers[i].availability) {
                onlineDriversQueue.emplace(Drivers[i]);
            }
        } int i = 1; 
        //Driver* closest = NULL;
        while (!onlineDriversQueue.empty()) {
            if (i == 6) { break; }

            Driver topDriver = onlineDriversQueue.top();
            double dis = CompareDrivers(LogedInrider->locX, LogedInrider->locY).distanceCal(LogedInrider->locX, LogedInrider->locY, onlineDriversQueue.top().locX, 
                onlineDriversQueue.top().locY);
            if (i == 1) {
                
                // closest = &RegMapD[onlineDriversQueue.top().username];
                auto finder1 = RegMapD.find(onlineDriversQueue.top().username);
                if (finder1 != RegMapD.end()) {
                    cout << "Driver found in RegMapD: " << topDriver.username << endl;
                    r1 = &finder1->second;
                    //r1 = closest;;
                }
                if (!r1) { cout << "Driver not found in RegMapD: " << topDriver.username << endl; return NULL; }
                
            }
            cout << i++ << ". " << topDriver.username << " " << dis << endl;
            onlineDriversQueue.pop();
        }

        return r1;
    }
    else { return NULL; }

}
bool Ridesystem::requestDriver() {
    if (LogedinAs) {
        Driver* r1 = this->onlineDrivers();
        cout << r1->username << endl;
        if (r1) {
            thread t1(&Ridesystem::rideinProcess, this, LogedInrider, r1, 10);
            t1.detach();
            return true;
        }
        else {
            cout<< "Driver pointer is null." << endl;
            return 0;
        }
        
        
    }
    else return 0;
}
void Ridesystem::rideinProcess(Rider* r, Driver* d,double time) {
    cout << "Ride started with rider: " << r->username << " id: " << r->uniqueId;
    cout << " with driver: " << d->username << " id: " << d->uniqueId <<" time of: "<<time<<" seconds." << endl;
    d->availability = 0;
    this_thread::sleep_for(chrono::seconds(int(time)));
    d->availability = 1;
    cout << "Ride completed for driver: " << d->username << " id: " << d->uniqueId << endl;

}

Ridesystem::~Ridesystem() {
    this->saveDriver();
    this->saveRider();
}
