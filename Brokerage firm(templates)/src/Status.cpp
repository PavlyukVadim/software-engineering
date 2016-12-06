#include "Status.h"


Status::~Status() { }


void Status::changeSt(int st) {
    status = st;
}

int Status::getSt() {
    return status;
}
