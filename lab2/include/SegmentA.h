#ifndef SEGMENTA_H
#define SEGMENTA_H

#include "Point.h"

class SegmentA : public Point{
    public:
    int x2, y2;
    float length;
        SegmentA();
        SegmentA(int n_x1, int n_y1, int n_x2, int n_y2): Point(n_x1, n_y1), x2(n_x2), y2(n_y2) { };
    void findLength();
};

#endif // SEGMENTA_H
