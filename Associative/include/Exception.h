#ifndef EXCEPTION_H
#define EXCEPTION_H


class Exception {
    private:
        char* msg;
    public:
        Exception(char* m);
        ~Exception();

        void show(void);
};

#endif // EXCEPTION_H
