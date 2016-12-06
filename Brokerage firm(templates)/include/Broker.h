#include <string>

using namespace std;

class Broker
{
    int nTransaction;
    int nCompletedTransaction;
    string name;

    public:
        Broker();
        Broker(string);
        virtual ~Broker();
        void addTransaction();
        void addCompletedTransaction();
        string getBrokerName();
        void outputBrokerInfo();
};
