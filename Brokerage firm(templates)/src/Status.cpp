#include "Status.h"

Status::Status() {
    status = 0;
}

Status::~Status() { }


void Status::changeSt(int st) {
    status = st;
}

int Status::getSt() {
    return status;
}
