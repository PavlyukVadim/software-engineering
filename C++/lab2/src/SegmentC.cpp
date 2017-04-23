#include "SegmentC.h"
#include "math.h"

void SegmentC::findLength() {
    length = sqrt( pow((x - x2), 2) + pow((y - y2), 2) );
}

