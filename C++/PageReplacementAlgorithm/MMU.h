#include "PageDescriptor.h"
#include <vector>

using namespace std;

class MMU
{
    public:
        MMU(int);
        void outputPageTable();

    protected:

    private:
        int numberOfFrameInVirtualMemory;
        vector<VirtualPageDescriptor> pageTable;
};
