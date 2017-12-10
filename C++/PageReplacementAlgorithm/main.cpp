#include <iostream>
#include "MMU.h"

using namespace std;

int main()
{
    int framesInPhysicalMemory;
    cout << "Input number of frames in the physical memory: ";
    cin >> framesInPhysicalMemory;

    MMU mmu(framesInPhysicalMemory);
    mmu.outputPageTable();

    return 0;
}
