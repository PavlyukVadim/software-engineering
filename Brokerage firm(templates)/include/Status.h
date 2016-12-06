#include <string>

using namespace std;


class Status
{
    int status;

    string description[5] = {
        "1",
        "2",
        "3",
        "4",
        "5"
    };
    public:
        Status();
        virtual ~Status();
        void changeSt(int);
        int getSt();

};

