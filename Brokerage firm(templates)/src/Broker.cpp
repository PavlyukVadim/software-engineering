#include "Broker.h"
#include <iostream>

using namespace std;

Broker::Broker() {
    name = "Anonim";
    nTransaction = 0;
    nCompletedTransaction = 0;
}

Broker::Broker(string bName) {
    name = bName;
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

void Broker::outputBrokerInfo() {
    cout << " Name: " << name << endl;
    cout << " Number of active transactions: " << nTransaction << endl;
    cout << " Number of completed transactions: " << nCompletedTransaction << endl;
}
