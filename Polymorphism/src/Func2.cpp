#include "Func2.h"

#include <math.h>
#include <iostream>

using namespace std;

void Func2::calculating() {
    cout << "(sin(x) + 3 * z^y - z * y) = "  << (sin(x) + 3 * pow(z, y) - z * y) << endl << endl;
}

Func2::~Func2() {

}
