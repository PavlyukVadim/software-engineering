#include "MMU.h"
#include <iostream>
#include <math.h>
#include "PageDescriptor.h"

using namespace std;

MMU::MMU(int framesInPhysicalMemory) {
    logger = new Logger();
    numberOfFramesInPhysicalMemory = framesInPhysicalMemory;
    numberOfFrameInVirtualMemory = 1.5 * framesInPhysicalMemory;
    string notification = "Initialization of MMU with: \n";
    string framesInPhysicalMemoryStr = ' ' + to_string(framesInPhysicalMemory) + ' ' + "frames in physical memory" + '\n';
    string numberOfFrameInVirtualMemoryStr = ' ' + to_string(numberOfFrameInVirtualMemory) + ' ' + "frames in virtual memory" + '\n';
    cout << notification << framesInPhysicalMemoryStr << numberOfFrameInVirtualMemoryStr;
    logger->writeToFile(notification);
    logger->writeToFile(framesInPhysicalMemoryStr);
    logger->writeToFile(numberOfFrameInVirtualMemoryStr);
    setInitialStateOfPageTable();
}

MMU::~MMU() {
    delete logger;
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
    string notification = "make reference to " + to_string(indexOfPage) + " virtual page: \n";
    logger->writeToFile(notification);

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
    outputPageTable();
}

void MMU::modifyVirtualPage(int indexOfPage) {
    string notification = "modify " + to_string(indexOfPage) + " virtual page: \n";
    logger->writeToFile(notification);

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
    outputPageTable();
}

void MMU::outputPageTable() {
    string header = "---------------\n# | R M P\n";
    cout << header;
    logger->writeToFile(header);
    for(int i = 0; i < pageTable.size(); i++) {
        string info = to_string(pageTable[i]->indexOfFrameInPhysicalMemory) + " | " +
                      to_string(pageTable[i]->R) + ' ' +
                      to_string(pageTable[i]->M) + ' ' +
                      pageTable[i]->place + '\n';
        cout << info;
        logger->writeToFile(info);
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
    string notification = "found new frame in physical memory: ";
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
            logger->writeToFile(notification + to_string(i) + '\n');
            return i;

        }
        if (classes[i] < minClass) {
            minClass = classes[i];
            indexOfMin = i;
        }
    }
    logger->writeToFile(notification + to_string(indexOfMin) + '\n');
    return indexOfMin;
}

void MMU::callTimer() {
    string notification = "callTimer: \n";
    logger->writeToFile(notification);

    int N = pageTable.size();
    for(int i = 0; i < N; i++) {
        if (pageTable[i]->place == 'M') {
            pageTable[i]->R = false;
        }
    }
    outputPageTable();
}
