#include "Broker.h"
#include "Client.h"
#include "Status.h"
//#include "Collection.h"
#include <vector>
#include <tuple>

using namespace std;

class BrokerageFirm
{
    vector<Broker> brokers;
    vector<Client> clients;
    //Collection<Client, Broker, Status>* collection; // templates - collection
    vector< tuple<Client, Broker, Status> > collection;

    public:
        BrokerageFirm();
        virtual ~BrokerageFirm();

        void addBroker(string name);
        void addClient(string cName, string cPhone, int aNRooms, double aSq, string addr);

        void outputBrokersInfo();
        void outputClientsInfo();

        void addTrBr(string);
        void addCTrBr(string);

        Broker searchFreeBroker(); // serch free broker
        void outputCollection();
        void overviewApartment(string addr);
        void buyApartment(string addr);
        void changeDays(int days);
        void nextStatus(); // change status of transaction on next
};
