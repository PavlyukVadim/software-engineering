#include "SegmentA.h"
#include "math.h"

void SegmentA::findLength() {
    length = sqrt( pow((x - x2), 2) + pow((y - y2), 2) );
}
