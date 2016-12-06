/* using std */


#include <iostream>
#include <string>

#include "BrokerageFirm.h"

using namespace std;

void addBroker(); // add new broker
void brokersInfo(); // output info about brokers
void addClient(); // add new client
void clientsInfo(); // output info about brokers

void OverviewApartment();
void BuyApartment();

void outputCollection();
void changeTime();


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
        cout << "7. Collection info" << endl;
        cout << "8. Change time" << endl;
        cout << "9. Clear screen" << endl;
        cout << "e. Exit" << endl;

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
            case '7' :  { outputCollection(); break; }
            case '8' :  { changeTime(); break; }
            case '9' :  { system("clear"); break; }
            case 'e' :  return 0;
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

    cout << "Input apartment address : ";
    cin >> addr;
    firm.overviewApartment(addr);
}

void BuyApartment() {
    string addr;

    cout << "Input apartment address : ";
    cin >> addr;
    firm.buyApartment(addr);
}

void outputCollection() {
    firm.outputCollection();
}


void changeTime() {
    int days;
    cout << "Input numder of days: " << endl;
    cin >> days;
    firm.changeDays(days);
}
