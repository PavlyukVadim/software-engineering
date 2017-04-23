#include <string>

using namespace std;


class Status
{
    int status; /*
        0 - apartment in database
        1 - waiting rooms review
        2 - waiting for the signature of the contract
        3 - paperwork
        4 - sold out
    */

    string description[5] = {
        "apartment in database",
        "waiting rooms review",
        "waiting for the signature of the contract",
        "paperwork",
        "sold out !"
    };
    public:
        Status() { };
        Status(int st) : status(st) { };
        virtual ~Status();
        void changeSt(int);
        string getDescSt();
        int getSt();

};

