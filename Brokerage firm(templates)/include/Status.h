#include <string>

using namespace std;


class Status
{
    int status;

    string description[5] = {
        "apartment in database",
        "waiting rooms review",
        "waiting for the signature of the contract",
        "paperwork",
        "sold Out"
    };
    public:
        Status() { };
        Status(int st) : status(st) { };
        virtual ~Status();
        void changeSt(int);
        string getDescSt();
        int getSt();

};

