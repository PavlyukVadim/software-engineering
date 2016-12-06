#include <string>

using namespace std;

class Broker
{
    int nTransaction; // number of transaction
    int nCompletedTransaction; // number of competed transaction
    string name;
    int timeTo; // time to next event

    public:
        Broker();
        Broker(string bName) : name(bName), timeTo(0), nTransaction(0), nCompletedTransaction(0) { }
        virtual ~Broker();
        void addTransaction();
        void addCompletedTransaction();
        string getBrokerName();
        int getTimeTo();
        void setTimeTo(int time);
        void outputBrokerInfo();
};
