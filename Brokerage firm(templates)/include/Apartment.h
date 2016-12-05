#include <string>

using namespace std;

class Apartment
{
    int numberOfRooms;
    double square;
    string addr;

    public:
        Apartment(){};
        Apartment(int nRooms, double sq): numberOfRooms(nRooms), square(sq){};
        void setParams(int, double, string);
        int getNumberOfRooms();
        double getSquare();
        void outputApartmentInfo();
        virtual ~Apartment();
};
