#include <vector>
#include "PageDescriptor.h"
#include "Logger.h"

using namespace std;

class MMU
{
    public:
        MMU(int);
        virtual ~MMU();
        void outputPageTable();
        void makeReferenceToVirtualPage(int);
        void modifyVirtualPage(int);
        void callTimer();

    protected:

    private:
        Logger* logger;
        int numberOfFramesInPhysicalMemory;
        int numberOfFrameInVirtualMemory;
        vector<VirtualPageDescriptor*> pageTable;

        void setInitialStateOfPageTable();
        bool checkIsFreeFrameInPhysicalMemory();
        int foundNewFrameInPhysicalMemory();
};
