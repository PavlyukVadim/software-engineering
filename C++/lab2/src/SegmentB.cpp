#include "SegmentB.h"
#include "math.h"

void SegmentB::findLength() {
    length = sqrt( pow((x - x2), 2) + pow((y - y2), 2) );
}

