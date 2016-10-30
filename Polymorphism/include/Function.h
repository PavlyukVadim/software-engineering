#ifndef FUNCTION_H
#define FUNCTION_H


class Func
{
    public:
        double x, y, z;
        Func();
        Func(double x1, double y1, double z1): x(x1), z(z1), y(y1) {};
        virtual void calculating() = 0;
};

#endif // FUNCTION_H
