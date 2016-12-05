class Apartment
{
    int numberOfRooms;
    double square;

    public:
        Apartment(int nRooms, double sq): numberOfRooms(nRooms), square(sq){};
        int getNumberOfRooms();
        double getSquare();
        void outputApartmentInfo();
        virtual ~Apartment();
};
