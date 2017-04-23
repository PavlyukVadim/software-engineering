#include "Point.h"
#include<iostream>

using namespace std;

Point::Point(int p_x, int p_y) {
    x = p_x;
    y = p_y;
}

void Point::get_Point(){
    cout << "Point : " << endl;
    cout << "x: " << x << " " << "y: " << y << endl;
}
