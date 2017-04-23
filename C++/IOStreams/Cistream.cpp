#include "Cistream.h"

Cistream::Cistream() { }

Cistream::~Cistream() { }

int Cistream::getData() {
    return data;
}

void Cistream::setData(int data_) {
    data = data_;
}
