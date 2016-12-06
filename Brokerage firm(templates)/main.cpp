#include <iostream>
#include <string>

#include "BrokerageFirm.h"

using namespace std;

void addBroker();
void brokersInfo();
void addClient();
void clientsInfo();

void OverviewApartment();
void BuyApartment();


BrokerageFirm firm;

int main()
{

    cout << "Pavlyuk Vadim Ruslanovych" << endl;
    cout << "V : 14" << endl;
    cout << "L : B" << endl << endl;

    bool cont = true;

    do {
        cout << "1. Add broker" << endl;
        cout << "2. Add client" << endl;
        cout << "3. Overview apartment" << endl;
        cout << "4. Buy apartment" << endl;
        cout << "5. Brokers info" << endl;
        cout << "6. Clients info" << endl;
        cout << "7. Clear screen" << endl;
        cout << "8. Exit" << endl;

        string sc;
        cin >> sc;

        char c = sc[0];

        switch(c) {
            case '1' :  { addBroker(); break; }
            case '2' :  { addClient(); break; }
            case '3' :  { OverviewApartment(); break; }
            case '4' :  { BuyApartment(); break; }
            case '5' :  { brokersInfo(); break; }
            case '6' :  { clientsInfo(); break; }
            case '7' :  { system("clear"); break; }
            case '8' :  return 0;
        }

    } while (cont);

    return 0;
}

void addBroker() {
    string name;
    cout << "Input broker name : ";
    cin >> name;
    firm.addBroker(name);
}

void brokersInfo() {
    firm.outputBrokersInfo();
}

void addClient() {
    string name, phone, addr;
    int aNRooms;
    double aSq;

    cout << "Input client name : ";
    cin >> name;
    cout << "Input client phone : ";
    cin >> phone;
    cout << "Input number of room : ";
    cin >> aNRooms;
    cout << "Input square : ";
    cin >> aSq;
    cout << "Input address : ";
    cin >> addr;

    firm.addClient(name, phone, aNRooms, aSq, addr);
}

void clientsInfo() {
    firm.outputClientsInfo();
}

void OverviewApartment() {
    string addr;
    cin >> addr;


}

void BuyApartment() {

}
