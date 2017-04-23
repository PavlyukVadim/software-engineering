#include "Func2.h"

#include <math.h>
#include <iostream>

using namespace std;

void Func2::calculating() {

    /*cout << "X: "; cin >> x;
    cout << "Y: "; cin >> y;
    cout << "Z: "; cin >> z;
    */
    if (!z && !y) {
        cout << "Невизначеність" << endl;
        return;
    }

    cout << "x: " << x << endl;
    cout << "y: " << y << endl;
    cout << "z: " << z << endl;

    cout << "(sin(x) + 3 * z^y - z * y) = "  << (sin(x) + 3 * pow(z, y) - z * y) << endl << endl;
}

Func2::~Func2() {

}
