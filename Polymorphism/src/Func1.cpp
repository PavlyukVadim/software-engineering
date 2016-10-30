#include "Func1.h"

#include <math.h>
#include <iostream>

using namespace std;

void Func1::calculating(){
    cout << "(7 * x^4 + √3xy) = "  << (7 * pow(x, 4) + sqrt(3 * x * y)) << endl;
}
