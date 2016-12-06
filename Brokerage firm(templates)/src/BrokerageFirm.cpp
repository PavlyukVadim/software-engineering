#include "BrokerageFirm.h"
#include <iostream>

using namespace std;

BrokerageFirm::BrokerageFirm() {
    cout << "Welcome to our firm !" << endl;
}

BrokerageFirm::~BrokerageFirm() { }

void BrokerageFirm::addBroker(string name) {
    brokers.push_back(Broker(name));
}

void BrokerageFirm::outputBrokersInfo() {
    cout << "Brokers : " << endl;
    for (int i = 0; i < brokers.size(); i++) {
        cout << "Broker #" << i + 1 << endl;
        brokers[i].outputBrokerInfo();
        cout << endl;
    }
}

void BrokerageFirm::addClient(string cName, string cPhone, int aNRooms, double aSq, string addr) {
    clients.push_back(Client(cName, cPhone, aNRooms, aSq, addr));


}

void BrokerageFirm::outputClientsInfo() {
    cout << "Clients : " << endl;
    for (int i = 0; i < clients.size(); i++) {
        cout << "Client #" << i + 1 << endl;
        clients[i].outputClientInfo();
        cout << endl;
    }
}
