#include "Broker.h"
#include "Client.h"
#include <vector>

using namespace std;

class BrokerageFirm
{
    vector<Broker> brokers;

    public:
        BrokerageFirm();
        virtual ~BrokerageFirm();
        void addBroker(string name);
        void outputBrokersInfo();
};
