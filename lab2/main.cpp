#include <iostream>
#include "Point.h"
#include "Triangle.h"

using namespace std;

int main()
{
    int s1_x1, s1_y1, s1_x2, s1_y2,
        s2_x1, s2_y1, s2_x2, s2_y2,
        s3_x1, s3_y1, s3_x2, s3_y2;

    cout << endl << "SegmentA :" << endl;
    cout << "X1 : ";
    cin >> s1_x1;
    cout << "Y1 : ";
    cin >> s1_y1;
    cout << "X2 : ";
    cin >> s1_x2;
    cout << "Y2 : ";
    cin >> s1_y2;

    cout << endl << "SegmentB :" << endl;
    cout << "X1 : ";
    cin >> s2_x1;
    cout << "Y1 : ";
    cin >> s2_y1;
    cout << "X2 : ";
    cin >> s2_x2;
    cout << "Y2 : ";
    cin >> s2_y2;

    cout << endl << "SegmentC :" << endl;
    cout << "X1 : ";
    cin >> s3_x1;
    cout << "Y1 : ";
    cin >> s3_y1;
    cout << "X2 : ";
    cin >> s3_x2;
    cout << "Y2 : ";
    cin >> s3_y2;

    Triangle* triangle = new Triangle(SegmentA(s1_x1, s1_y1, s1_x2, s1_y2), SegmentB(s2_x1, s2_y1, s2_x2, s2_y2), SegmentC(s3_x1, s3_y1, s3_x2, s3_y2));

    triangle->checkTriangle();
    triangle->findSquare();

    return 0;
}
