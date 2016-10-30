#ifndef FUNC2_H
#define FUNC2_H

#include "Function.h"

class Func2 : public Func
{
    public:
        Func2(double x1, double y1, double z1): Func(x1, y1, z1) {};
        void calculating();
};

#endif // FUNC1_H
