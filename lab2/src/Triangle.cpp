#include "Triangle.h"
#include <iostream>
#include <math.h>

using namespace std;

void Triangle::checkTriangle() {
    segmentA.findLength();
    segmentB.findLength();
    segmentC.findLength();

    if ((segmentA.length < segmentB.length + segmentC.length) &&
        (segmentB.length < segmentA.length + segmentC.length) &&
        (segmentC.length < segmentA.length + segmentB.length)) {
        exist = true;
    }
    else {
        exist = false;
    }
}

void Triangle::findSquare() {
    if (!exist) {
        cout << "Triandle isn't exist" << endl;
        return;
    }

    float square = 0,
          p = (segmentA.length + segmentB.length + segmentC.length) / 2;
    square = sqrt(p * (p - segmentA.length) * (p - segmentB.length) * (p - segmentC.length));
    cout << "Square: " << square << endl;
}
