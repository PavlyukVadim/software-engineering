class Apartment
{
    int numberOfRooms;
    double square;

    public:
        Apartment(){};
        Apartment(int nRooms, double sq): numberOfRooms(nRooms), square(sq){};
        void setParams(int, double);
        int getNumberOfRooms();
        double getSquare();
        void outputApartmentInfo();
        virtual ~Apartment();
};
