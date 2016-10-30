#ifndef FUNC1_H
#define FUNC1_H

#include "Function.h"

class func2 : public Func
{
    public:
        func2(double x1, double y1, double z1): Func(x1, y1, z1) {};
        void calculating();
};

#endif // FUNC1_H
