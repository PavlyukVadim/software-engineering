#include "Status.h"


Status::~Status() { }


void Status::changeSt(int st) {
    status = st;
}

int Status::getSt() {
    return status;
}

string Status::getDescSt() {
    return description[status];
}
