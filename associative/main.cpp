#include <iostream>
#include "associative.h"
#include <string.h>

int main() {

    AssociativeArray A;

    A << "lol";
    A << "cat";
    A << "hihik";
    A << "aaaa";
    A << "bbbb";

    AssociativeArray B;
    B << "love";
    B << "sex";
    B << "cat";

    A["lol"] = "ahahaha";
    //cout << A["lol"];

    //A += B;
    A = A + B;

    A.output(A.root, 0);

    return 0;
}
