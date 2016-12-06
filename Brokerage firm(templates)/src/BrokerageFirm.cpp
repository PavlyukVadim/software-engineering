#include "BrokerageFirm.h"
#include <iostream>
#include <algorithm>

using namespace std;

BrokerageFirm::BrokerageFirm() {
    cout << "Welcome to our firm !" << endl;
    collection = new Collection<Client, Broker, Status>[100];
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
    collection[clients.size()] = Collection<Client, Broker, Status>({cName, cPhone, aNRooms, aSq, addr},{"Max"}, {0});

    if( !brokers.size() ) {
        cout << "The company has no broker" << endl;
        return;
    }
    searchFreeBroker();
    //collection[0].outputBrokerInfo();
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


Broker BrokerageFirm::searchFreeBroker() {
    Broker broker;
    int *brorerEmployment = new int [brokers.size()];
    for (int i = 0; i < brokers.size(); i++) {
        brorerEmployment[i] = 0;
        string name = brokers[i].getBrokerName();
        for (int j = 0; j < clients.size(); j++) {
            if(collection[j].getBrokerName() == name) {
                if (collection[j].getSt() == 0 || collection[j].getSt() == 4) {
                    brorerEmployment[i] = 0;
                }
                else {
                    brorerEmployment[i] += collection[j].getSt();
                }
            }
        }
    }

    int minEmployment = brorerEmployment[0];
    broker = brokers[0];
    for (int i = 1; i < brokers.size(); i++) {
        if(brorerEmployment[i] < minEmployment) {
            minEmployment = brorerEmployment[i];
            broker = brokers[i];
        }
    }
    //cout << minEmployment << endl;
    return broker;
}
