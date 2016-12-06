#include "Client.h"
#include <iostream>

using namespace std;

Client::Client() { }

Client::~Client() { }

Client::Client(string cName, string cPhone, int aNRooms, double aSq, string addr) {
    name = cName;
    phone = cPhone;
    apartment.setParams(aNRooms, aSq, addr);
}

void Client::setPhone(string ph) {
    phone = ph;
}

string Client::getName() {
    return name;
}

string Client::getPhone() {
    return phone;
}

void Client::outputClientInfo() {
    cout << " Name: " << name << endl;
    cout << " Phone: " << phone << endl;
    apartment.outputApartmentInfo();
}
