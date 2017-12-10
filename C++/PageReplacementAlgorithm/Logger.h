#include <fstream>

using namespace std;

class Logger
{
    public:
        Logger() : outFile("outFile.txt") {};
        virtual ~Logger();
        void writeToFile(string);

    protected:

    private:
        ofstream outFile;
};
