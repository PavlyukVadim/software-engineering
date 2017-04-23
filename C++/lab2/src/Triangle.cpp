#include "Triangle.h"
#include <iostream>
#include <math.h>

using namespace std;




void Triangle::checkTriangle() {
    segmentA.findLength();
    segmentB.findLength();
    segmentC.findLength();

    Triangle::M arr;

    if ((segmentA.length < segmentB.length + segmentC.length) &&
        (segmentB.length < segmentA.length + segmentC.length) &&
        (segmentC.length < segmentA.length + segmentB.length)) {
        exist = true;

        int counter = 6;
        int pos = 0;

         Triangle::Push(arr, segmentA.x, segmentA.y, pos);
         Triangle::Push(arr, segmentA.x2, segmentA.y2, pos);
         Triangle::Push(arr, segmentB.x, segmentB.y, pos);
         Triangle::Push(arr, segmentB.x2, segmentB.y2, pos);
         Triangle::Push(arr, segmentC.x, segmentC.y, pos);
         Triangle::Push(arr, segmentC.x2, segmentC.y2, pos);

    if (pos > 2) {
        exist = false;
    }
    cout << "count unique " << pos + 1 << endl;
    }

    else {
        exist = false;
    }
}

void Triangle::Push(Triangle::M &arr, int x, int y, int &pos) {
    for (int i = 0; i < 12; i++) {
        if (arr.x1[i] == x && arr.y1[i] == y) {
            return;
        }
    }

    arr.x1[pos] = x;
    arr.y1[pos] = y;
    pos++;
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

