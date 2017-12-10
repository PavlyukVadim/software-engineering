#include "PageDescriptor.h"
#include <vector>

using namespace std;

class MMU
{
    public:
        MMU(int);
        void outputPageTable();
        void makeReferenceToVirtualPage(int);
        void modifyVirtualPage(int);

    protected:

    private:
        int numberOfFramesInPhysicalMemory;
        int numberOfFrameInVirtualMemory;
        vector<VirtualPageDescriptor*> pageTable;

        void setInitialStateOfPageTable();
        bool checkIsFreeFrameInPhysicalMemory();
        int foundNewFrameInPhysicalMemory();
};
