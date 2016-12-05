#include "Broker.h"
#include <iostream>

using namespace std;

Broker::Broker() {
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
    cout << "Number of active transactions: " << nTransaction << endl;
    cout << "Number of completed transactions: " << nCompletedTransaction << endl;
}
