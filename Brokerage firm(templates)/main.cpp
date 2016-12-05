#include <iostream>
#include "Client.h"

using namespace std;

int main()
{
    /*Apartment apartment;
    apartment.setParams(5, 85, "Mira 65");
    apartment.outputApartmentInfo();*/

    Client client("Max", "+38098 777 77 07", 5, 85, "Mira 90");
    client.outputClientInfo();

    return 0;
}
