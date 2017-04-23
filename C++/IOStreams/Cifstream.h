#include <iostream>
#include <fstream>

using namespace std;

class Cifstream
{
    public:
        fstream fs;
        string fileName;
        Cifstream();
        Cifstream(string fileName_);
        void Open();
        void Close();
        virtual ~Cifstream();

    protected:

    private:
};
