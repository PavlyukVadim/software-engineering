#ifndef SEGMENTB_H
#define SEGMENTB_H

#include "Point.h"

class SegmentB : public Point{
    public:
    int x2, y2;
    float length;
        SegmentB();
        SegmentB(int n_x1, int n_y1, int n_x2, int n_y2): Point(n_x1, n_y1), x2(n_x2), y2(n_y2) { };
    void findLength();
};
#endif // SEGMENTB_H
