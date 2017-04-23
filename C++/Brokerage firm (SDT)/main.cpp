/* using std */

#include <iostream>
#include <string>
#include <random>

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


const int numberOfBrokers = 10;
int numberOfEmpBrok = 0;
int employedBrokers[numberOfBrokers] = {0};
string brokersNames[numberOfBrokers] = {"Jackson", "Aiden", "Lucas",
                                        "Liam", "Noah", "Ethan",
                                        "Mason", "Caden", "Oliver", "Elijah"};

const int numberOfClients = 10;
int numberOfEmpClients = 0;
int employedClients[numberOfClients] = {0};
int completeClients[numberOfClients] = {0};
string clientsNames[numberOfClients] = {"Sophia", "Emma", "Olivia",
                                        "Ava", "Mia", "Isabella",
                                        "Riley", "Aria", "Zoe", "Charlotte"};

string clientsAddr[numberOfClients] = { "Mira90", "Mira91", "Mira92",
                                        "Mira93", "Mira94", "Mira95",
                                        "Mira96", "Mira97", "Mira98",
                                        "Mira99" };

string clientsPhone[numberOfClients] = { "+38 097 77 77 777", "+38 097 77 77 778", "+38 097 77 77 779",
                                         "+38 097 77 77 780", "+38 097 77 77 781", "+38 097 77 77 782",
                                         "+38 097 77 77 783", "+38 097 77 77 784", "+38 097 77 77 785",
                                         "+38 097 77 77 786" };



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
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 10);
    string name;

    if (numberOfEmpBrok == numberOfBrokers) {
        cout << "All brokers added" << endl;
        return;
    }

    bool findb = false;
    while(!findb) {
         int number = dist(gen);
         if(!employedBrokers[number - 1]) {
            findb = true;
            name = brokersNames[number - 1];
            numberOfEmpBrok++;
            employedBrokers[number - 1] = 1;
         }
    }
    cout << "Broker name : " << name << endl;

    /*for (int i = 0; i <= 5; i++) {
        cout << dist(gen) << " ";
    }*/
    firm.addBroker(name);
}

void brokersInfo() {
    firm.outputBrokersInfo();
}

void addClient() {

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 10);
    uniform_int_distribution<int> sq(60, 150); // for sq
    uniform_int_distribution<int> nr(1, 4); // for number of room
    string name, phone, addr;
    int aNRooms;
    double aSq;

    if (numberOfEmpClients == numberOfClients) {
        cout << "All clients added" << endl;
        return;
    }

    bool findc = false;
    while(!findc) {
         int number = dist(gen);
         if(!employedClients[number - 1]) {
            findc = true;
            name = clientsNames[number - 1];
            addr = clientsAddr[number - 1];
            phone = clientsPhone[number - 1];
            aSq = sq(gen);
            aNRooms = nr(gen);
            numberOfEmpClients++;
            employedClients[number - 1] = 1;
         }
    }

    cout << "Client name : " << name << endl;
    cout << "Client phone : " << phone << endl;
    cout << "Apartment: " << endl;
    cout << " Number of room : " << aNRooms << endl;
    cout << " Square : " << aSq << endl;
    cout << " Address : " << addr << endl;

    firm.addClient(name, phone, aNRooms, aSq, addr);
}

void clientsInfo() {
    firm.outputClientsInfo();
}

void OverviewApartment() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 10);
    string addr;

    if(!numberOfEmpClients) {
        cout << "No customer." << endl;
        return;
    }

    int count_free = 0;
    for(int i = 0; i < numberOfClients; i++) {
        if(employedClients[i] && !completeClients[i]) {
            count_free++;
        }
    }
    if(!count_free) {
        cout << "All apartments sold!" << endl;
        return;
    }


    bool finda = false;
    while(!finda) {
         int number = dist(gen);
         if(employedClients[number - 1] && !completeClients[number - 1]) {
            finda = true;
            addr = clientsAddr[number - 1];
         }
    }

    cout << "Apartment address : " << addr << endl;
    firm.overviewApartment(addr);
}

void BuyApartment() {

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 10);
    string addr;

    if(!numberOfEmpClients) {
        cout << "No customer." << endl;
        return;
    }

    int count_free = 0;
    for(int i = 0; i < numberOfClients; i++) {
        if(employedClients[i] && !completeClients[i]) {
            count_free++;
        }
    }
    if(!count_free) {
        cout << "All apartments sold!" << endl;
        return;
    }

    bool finda = false;
    while(!finda) {
         int number = dist(gen);
         if(employedClients[number - 1] && !completeClients[number - 1]) {
            finda = true;
            addr = clientsAddr[number - 1];
            completeClients[number - 1] = 1;
         }
    }

    cout << "Apartment address : " << addr << endl;
    firm.buyApartment(addr);
}

void outputCollection() {
    firm.outputCollection();
}


void changeTime() {

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 3);

    int days = dist(gen) * 5;
    cout << "Numder of days: " << days << endl;
    firm.changeDays(days);
}
