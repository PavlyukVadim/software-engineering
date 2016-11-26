#include "Func1.h"

#include <math.h>
#include <iostream>

using namespace std;


void Func1::calculating(){
    /*cout << "X: "; cin >> x;
    cout << "Y: "; cin >> y;
    cout << "Z: "; cin >> z;
    */
    if (x * y < 0) {
        cout << "x * y < 0" << endl;
        return;
    }
    cout << "x: " << x << endl;
    cout << "y: " << y << endl;
    cout << "z: " << z << endl;

    cout << "(7 * x^4 + √3xy) = "  << (7 * pow(x, 4) + sqrt(3 * x * y)) << endl << endl;
}

Func1::~Func1() {

}
