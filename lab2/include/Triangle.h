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


        Triangle(SegmentA n_segmentA, SegmentB n_segmentB, SegmentC n_segmentC): segmentA(n_segmentA), segmentB(n_segmentB), segmentC(n_segmentC) { }
    bool exist;
    void checkTriangle();
    void findSquare();
};




#endif // TRIANGLE_H
