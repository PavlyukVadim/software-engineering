#include "func2.h"

#include <math.h>
#include <iostream>

using namespace std;

void func2::calculating(){
    cout << "(sin(x) + 3z^y - zy) = "  << (sin(x) + 3 * pow(z, y) - z * y);
}
