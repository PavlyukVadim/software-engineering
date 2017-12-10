#include <iostream>
#include "MMU.h"

using namespace std;

void makeReference(MMU* mmu) {
    int indexOfPage;
    string notification = "Input index of page: ";
    cout << notification;
    cin >> indexOfPage;
    cout << endl;
    mmu->makeReferenceToVirtualPage(indexOfPage);
}

void modifyPage(MMU* mmu) {
    int indexOfPage;
    cout << "Input index of page: ";
    cin >> indexOfPage;
    cout << endl;
    mmu->modifyVirtualPage(indexOfPage);
}

int main() {
    int framesInPhysicalMemory;
    cout << "Input number of frames in the physical memory: ";
    cin >> framesInPhysicalMemory;

    MMU* mmu = new MMU(framesInPhysicalMemory);

    bool cont = true;

    do {
        cout << endl;
        cout << "1. output pageTable" << endl;
        cout << "2. make reference to page" << endl;
        cout << "3. modify page" << endl;
        cout << "4. call timer" << endl;
        cout << "e. Exit" << endl;

        string sc;
        cin >> sc;

        char c = sc[0];

        switch(c) {
            case '1' :  { mmu->outputPageTable(); break; }
            case '2' :  { makeReference(mmu); break; }
            case '3' :  { modifyPage(mmu); break; }
            case '4' :  { mmu->callTimer(); break; }
            case 'e' :  { delete mmu; return 0; }
        }

    } while (cont);

    delete mmu;

    return 0;
}
