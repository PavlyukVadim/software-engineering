#include "MMU.h"
#include <iostream>
#include <math.h>
#include "PageDescriptor.h"

using namespace std;

MMU::MMU(int framesInPhysicalMemory)
{
    VirtualPageDescriptor vpd;
    numberOfFrameInVirtualMemory = 1.5 * framesInPhysicalMemory;
    cout << "Initialization of MMU with: " << endl;
    cout << " " << framesInPhysicalMemory << " " << "frames in physical memory" << endl;
    cout << " " << numberOfFrameInVirtualMemory << " " << "frames in virtual memory" << endl;

    vpd.R = true;
    pageTable.push_back(vpd);
    pageTable.push_back(vpd);
}

void MMU::outputPageTable() {
    for(int i = 0; i < pageTable.size(); i++)
    {
        cout << pageTable[i].R << 'a';
    }
}
