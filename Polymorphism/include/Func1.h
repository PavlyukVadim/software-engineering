#ifndef FUNC1_H
#define FUNC1_H

#include "Function.h"

class Func1 : public Func
{
    public:
        Func1(double x1, double y1, double z1): Func(x1, y1, z1) {};
        void calculating();
};

#endif // FUNC1_H
