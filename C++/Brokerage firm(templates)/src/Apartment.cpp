#include "Apartment.h"
#include<iostream>

using namespace std;

Apartment::~Apartment() { }

void Apartment::setParams(int nRooms, double sq, string ad) {
    numberOfRooms = nRooms;
    square = sq;
    addr = ad;
}

int Apartment::getNumberOfRooms() {
    return numberOfRooms;
}

double Apartment::getSquare() {
    return square;
}

void Apartment::outputApartmentInfo() {
    cout << " Apartment: " << endl;
    cout << " Number Of rooms: " << numberOfRooms << endl;
    cout << " Square: " << square << endl;
    cout << " Address: " << addr << endl;
}

string Apartment::getAddress() {
    return addr;
}
