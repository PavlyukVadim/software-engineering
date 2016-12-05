#include "Apartment.h"
#include<iostream>

using namespace std;

Apartment::~Apartment()
{
    //dtor
}


int Apartment::getNumberOfRooms() {
    return numberOfRooms;
}

double Apartment::getSquare() {
    return square;
}

void Apartment::outputApartmentInfo() {
    cout << "Number Of rooms: " << numberOfRooms << endl;
    cout << "Square: " << square << endl;
}
