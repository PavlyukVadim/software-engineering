#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "SegmentA.h"
#include "SegmentB.h"
#include "SegmentC.h"

class Triangle {
    public:
    SegmentA segmentA;
    SegmentB segmentB;
    SegmentC segmentC;

    struct M{
        int x1[12];
        int y1[12];
    };

        Triangle(SegmentA n_segmentA, SegmentB n_segmentB, SegmentC n_segmentC): segmentA(n_segmentA), segmentB(n_segmentB), segmentC(n_segmentC) { }
    bool exist;
    void checkTriangle();
    void findSquare();
    void Push(M &m, int x, int y, int &a);
};




#endif // TRIANGLE_H
