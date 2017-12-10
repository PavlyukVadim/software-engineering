#include "MMU.h"
#include <iostream>
#include <math.h>
#include "PageDescriptor.h"

using namespace std;

MMU::MMU(int framesInPhysicalMemory) {
    numberOfFramesInPhysicalMemory = framesInPhysicalMemory;
    numberOfFrameInVirtualMemory = 1.5 * framesInPhysicalMemory;
    cout << "Initialization of MMU with: " << endl;
    cout << " " << framesInPhysicalMemory << " " << "frames in physical memory" << endl;
    cout << " " << numberOfFrameInVirtualMemory << " " << "frames in virtual memory" << endl;

    setInitialStateOfPageTable();
}


void MMU::setInitialStateOfPageTable() {
    for (int i = 0; i < numberOfFramesInPhysicalMemory; i++) {
        VirtualPageDescriptor* vpd = new VirtualPageDescriptor;
        vpd->R = false;
        vpd->M = false;
        vpd->indexOfFrameInPhysicalMemory = i;
        pageTable.push_back(vpd);
    }
}

void MMU::makeReferenceToVirtualPage(int indexOfPage) {
    VirtualPageDescriptor* vpd = pageTable.at(indexOfPage);
    vpd->R = true;
}

void MMU::modifyVirtualPage(int indexOfPage) {
    VirtualPageDescriptor* vpd = pageTable.at(indexOfPage);
    vpd->R = true;
    vpd->M = true;
}

void MMU::outputPageTable() {
    cout << '#' << " " << '|' << " " << 'R' << " " << 'M' << endl;
    for(int i = 0; i < pageTable.size(); i++) {
        cout << pageTable[i]->indexOfFrameInPhysicalMemory << " " << '|' << " " << pageTable[i]->R << " " << pageTable[i]->M << " " << endl;
    }
}
