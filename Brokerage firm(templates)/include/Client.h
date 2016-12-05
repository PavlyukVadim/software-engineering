#include "Apartment.h"


class Client
{
    string name;
    string phone;

    Apartment apartment;

    public:
        Client();
        Client(string name, string phone, int aNRooms, double aSq, string addr);

        void setPhone(string);
        string getName();
        string getPhone();
        void outputClientInfo();

        virtual ~Client();
};
