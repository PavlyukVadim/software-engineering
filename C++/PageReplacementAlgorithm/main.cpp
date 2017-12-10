#include <iostream>
#include "MMU.h"

using namespace std;

void makeReference(MMU* mmu) {
    int indexOfPage;
    cout << "Input index of page: ";
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

int main()
{
    int framesInPhysicalMemory;
    cout << "Input number of frames in the physical memory: ";
    cin >> framesInPhysicalMemory;

    MMU mmu(framesInPhysicalMemory);

    bool cont = true;

    do {
        cout << endl;
        cout << "1. output pageTable" << endl;
        cout << "2. make reference to page" << endl;
        cout << "3. modify page" << endl;
        cout << "4. " << endl;
        cout << "5. " << endl;
        cout << "6. " << endl;
        cout << "7. " << endl;
        cout << "8. " << endl;
        cout << "9. " << endl;
        cout << "e. Exit" << endl;

        string sc;
        cin >> sc;

        char c = sc[0];

        switch(c) {
            case '1' :  { mmu.outputPageTable(); break; }
            case '2' :  { makeReference(&mmu); break; }
            case '3' :  { modifyPage(&mmu); break; }
           // case '4' :  { break; }
           // case '5' :  { break; }
           // case '6' :  { break; }
           // case '7' :  { break; }
           // case '8' :  { break; }
           // case '9' :  { break; }
            case 'e' :  return 0;
        }

    } while (cont);

    return 0;
}
