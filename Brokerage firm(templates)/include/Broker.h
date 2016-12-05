class Broker
{
    int nTransaction;
    int nCompletedTransaction;

    public:
        Broker();
        virtual ~Broker();
        void addTransaction();
        void addCompletedTransaction();
        void outputBrokerInfo();
};
