#include "BrokerageFirm.h"
#include <iostream>
#include <algorithm>

using namespace std;

BrokerageFirm::BrokerageFirm() {
    cout << "Welcome to our firm !" << endl;
    collection = new tuple<Client, Broker, Status>[100];
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


    if( !brokers.size() ) {
        cout << "The company has no broker" << endl;
        return;
    }

    Broker broker = searchFreeBroker();
    addTrBr(broker.getBrokerName());
    clients.push_back(Client(cName, cPhone, aNRooms, aSq, addr));
    collection[clients.size() - 1] = tuple<Client, Broker, Status>(Client(cName, cPhone, aNRooms, aSq, addr),
    Broker(broker.getBrokerName()), Status(0));
                                                                    /*{cName, cPhone, aNRooms, aSq, addr},
                                                                    {broker.getBrokerName()},
                                                                    {0}*/
                                                                // );
    outputCollection();

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
            if( get<1>(collection[j]).getBrokerName() == name) {
                if (get<2>(collection[j]).getSt() == 0 || get<2>(collection[j]).getSt() == 4) {
                    brorerEmployment[i] = 0;
                }
                else {
                    brorerEmployment[i] += get<2>(collection[j]).getSt();
                }
                cout << " " << brorerEmployment[i] << endl;
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
    cout << "minEmployment: " << minEmployment << endl;
    return broker;
}


void BrokerageFirm::outputCollection() {
    for (int i = 0; i < clients.size(); i++) {

        cout << endl << "Collection : " << endl;
        cout << "Client: " << "#" << i + 1 << endl;
        get<0>(collection[i]).outputClientInfo();
        cout << "Broker: " << endl;
        cout << " "  << get<1>(collection[i]).getBrokerName() << endl;
        cout << " Time to event: "  << get<1>(collection[i]).getTimeTo() << " days" << endl;
        cout << "Status : " << get<2>(collection[i]).getDescSt() << endl;
        cout << endl;
    }
}


void BrokerageFirm::overviewApartment(string addr) {
    for (int i = 0; i < clients.size(); i++) {
        if (get<0>(collection[i]).apartment.getAddress() == addr) {
            get<1>(collection[i]).setTimeTo(10);
            get<2>(collection[i]).changeSt(1);
            return;
        }
    }
    cout << "Apartment doesn't found" << endl;
}

void BrokerageFirm::buyApartment(string addr) {
    for (int i = 0; i < clients.size(); i++) {
        if (get<0>(collection[i]).apartment.getAddress() == addr) {
            get<1>(collection[i]).setTimeTo(5);
            get<2>(collection[i]).changeSt(2);
            return;
        }
    }
    cout << "Apartment doesn't found" << endl;
}

void BrokerageFirm::changeDays(int days) {
    for (int i = 0; i < clients.size(); i++) {
        if (get<1>(collection[i]).getTimeTo() > 0 && get<2>(collection[i]).getSt() != 4) {
            get<1>(collection[i]).setTimeTo(get<1>(collection[i]).getTimeTo() - days);
        }
    }
    nextStatus();
}

void BrokerageFirm::nextStatus() {
    for (int i = 0; i < clients.size(); i++) {
        if (get<2>(collection[i]).getSt() == 1 && get<1>(collection[i]).getTimeTo() <= 0) {
            get<2>(collection[i]).changeSt(0);
        }

        if (get<2>(collection[i]).getSt() == 2 && get<1>(collection[i]).getTimeTo() <= 0) {
            get<2>(collection[i]).changeSt(3);
            get<1>(collection[i]).setTimeTo(get<1>(collection[i]).getTimeTo() + 5);
            if (get<1>(collection[i]).getTimeTo() <= 0) {
                nextStatus();
                return;
            }
        }

        if (get<2>(collection[i]).getSt() == 3 && get<1>(collection[i]).getTimeTo() <= 0) {
            get<2>(collection[i]).changeSt(4);
            get<1>(collection[i]).setTimeTo(0);
            addCTrBr(get<1>(collection[i]).getBrokerName());
        }
    }
}


void BrokerageFirm::addTrBr(string name) {
    for (int i = 0; i < brokers.size(); i++) {
        if( name == brokers[i].getBrokerName() ) {
            brokers[i].addTransaction();
            return;
        }
    }
}

void BrokerageFirm::addCTrBr(string name) {
    for (int i = 0; i < brokers.size(); i++) {
        if( name == brokers[i].getBrokerName() ) {
            brokers[i].addCompletedTransaction();
            return;
        }
    }
}
