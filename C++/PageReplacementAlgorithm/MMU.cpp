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
    for (int i = 0; i < numberOfFrameInVirtualMemory; i++) {
        VirtualPageDescriptor* vpd = new VirtualPageDescriptor;
        vpd->R = false;
        vpd->M = false;
        vpd->indexOfFrameInPhysicalMemory = i;
        if (i < numberOfFramesInPhysicalMemory) {
            vpd->place = 'M';
        } else {
            vpd->place = 'D';
        }
        pageTable.push_back(vpd);
    }
}

void MMU::makeReferenceToVirtualPage(int indexOfPage) {
    VirtualPageDescriptor* vpd = pageTable.at(indexOfPage);
    if (vpd->place == 'M') {
        vpd->R = true;
    } else {
        int indexOfNewFrame = foundNewFrameInPhysicalMemory();
        VirtualPageDescriptor* vpdOfNewFrame = pageTable.at(indexOfNewFrame);
        vpdOfNewFrame->place = 'D';
        vpdOfNewFrame->M = false;
        vpd->place = 'M';
        vpd->R = true;
    }
}

void MMU::modifyVirtualPage(int indexOfPage) {
    VirtualPageDescriptor* vpd = pageTable.at(indexOfPage);
    if (vpd->place == 'M') {
        vpd->R = true;
        vpd->M = true;
    } else {
        int indexOfNewFrame = foundNewFrameInPhysicalMemory();
        VirtualPageDescriptor* vpdOfNewFrame = pageTable.at(indexOfNewFrame);
        vpdOfNewFrame->place = 'D';
        vpdOfNewFrame->M = false;
        vpd->place = 'M';
        vpd->R = true;
        vpd->M = true;
    }
}

void MMU::outputPageTable() {
    cout << '#' << " " << '|' << " " << 'R' << " " << 'M' << " " << "P" << endl;
    for(int i = 0; i < pageTable.size(); i++) {
        cout << pageTable[i]->indexOfFrameInPhysicalMemory << " " << '|' << " " << pageTable[i]->R << " " << pageTable[i]->M << " " << pageTable[i]->place << endl;
    }
}

bool MMU::checkIsFreeFrameInPhysicalMemory() {
    int numberOfFramesInMemory = 0;
    for(int i = 0; i < pageTable.size(); i++) {
        if (pageTable[i]->place == 'M') {
            numberOfFramesInMemory += 1;
        }
    }
    if (numberOfFramesInMemory == numberOfFramesInPhysicalMemory) {
        return false;
    }
    return true;
}

int MMU::foundNewFrameInPhysicalMemory() {
    int N = pageTable.size();
    int classes[N];
    for(int i = 0; i < N; i++) {
        if (pageTable[i]->place == 'M') {
            if (!pageTable[i]->R && pageTable[i]->M) {
                classes[i] = 1;
            } else if (pageTable[i]->R && !pageTable[i]->M) {
                classes[i] = 2;
            } else if (pageTable[i]->R && pageTable[i]->M) {
                classes[i] = 3;
            } else {
                classes[i] = 0;
            }
        } else {
            classes[i] = 4;
        }
    }

    int minClass = 4, indexOfMin;
    for(int i = 0; i < N; i++) {
        if (!classes[i]) {
            return i;
        }
        if (classes[i] < minClass) {
            minClass = classes[i];
            indexOfMin = i;
        }
    }
    return indexOfMin;
}
