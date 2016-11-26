#include <iostream>

#include "Func1.h"
#include "Func2.h"
#include "Function.h"

using namespace std;

int main()
{
    Func* functions[2];
    functions[0] = new Func1(1, 1, 1);
    functions[1] = new Func2(0, 1, 0);

    functions[0]->calculating();
    functions[1]->calculating();

    return 0;
}
