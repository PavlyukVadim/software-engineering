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
