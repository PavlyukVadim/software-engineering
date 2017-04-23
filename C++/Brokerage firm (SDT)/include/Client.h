#include "Apartment.h"


class Client
{
    string name;
    string phone;

    public:
        Apartment apartment;
        Client();
        Client(string name, string phone, int aNRooms, double aSq, string addr);

        void setPhone(string);
        string getName();
        string getPhone();
        void outputClientInfo();

        virtual ~Client();
};
