#include <iostream>
#include "Apartment.h"

using namespace std;

int main()
{
    Apartment apartment;
    apartment.setParams(5, 85, "Mira 65");
    apartment.outputApartmentInfo();

    return 0;
}
