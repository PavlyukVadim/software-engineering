#include "Broker.h"
#include <iostream>

using namespace std;

Broker::Broker() {
    name = "Anonim";
    nTransaction = 0;
    nCompletedTransaction = 0;
}

Broker::~Broker() { }

void Broker::addTransaction() {
    nTransaction += 1;
}

void Broker::addCompletedTransaction() {
    nCompletedTransaction += 1;
    nTransaction -= 1;
}

string Broker::getBrokerName() {
    return name;
}

int Broker::getTimeTo() {
    return timeTo;
}

void Broker::setTimeTo(int time) {
    timeTo = time;
}

void Broker::outputBrokerInfo() {
    cout << " Name: " << name << endl;
    cout << " Number of active transactions: " << nTransaction << endl;
    cout << " Number of completed transactions: " << nCompletedTransaction << endl;
}
