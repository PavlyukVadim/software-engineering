#include <iostream>

#include "Func1.h"
#include "Func2.h"

using namespace std;

int main()
{
    Func1 *func1 = new Func1(1, 1, 1);
    func1->calculating();

    Func2 *func2 = new Func2(0, 1, 1);
    func2->calculating();

    return 0;
}
