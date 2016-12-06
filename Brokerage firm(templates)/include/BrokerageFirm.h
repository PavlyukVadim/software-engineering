#include "Broker.h"
#include "Client.h"
#include "Collection.h"
#include <vector>

using namespace std;

class BrokerageFirm
{
    vector<Broker> brokers;
    vector<Client> clients;
    Collection<Client, Broker, int>* collection;

   /* Info<Client, Card> bankinfo({ "Ivanov Ivan", "555-55-55" }, { 123456789, "5/10/2016", "5/10/2018" });*/


    public:
        BrokerageFirm();
        virtual ~BrokerageFirm();

        void addBroker(string name);
        void addClient(string cName, string cPhone, int aNRooms, double aSq, string addr);

        void outputBrokersInfo();
        void outputClientsInfo();
};
