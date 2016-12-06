#include <iostream>
#include <string>

#include "BrokerageFirm.h"

using namespace std;


void addBroker();
void brokersInfo();


BrokerageFirm firm;

int main()
{

    cout << "Pavlyuk Vadim Ruslanovych" << endl;
    cout << "V : 14" << endl;
    cout << "L : B" << endl << endl;

    bool cont = true;

    do {
        cout << "1. Add broker" << endl;
        cout << "2. Add client" << endl;
        cout << "3. Buy apartment" << endl;
        cout << "4. Brokers info" << endl;
        cout << "5. Exit" << endl;

        string sc;
        cin >> sc;

        char c = sc[0];

        switch(c) {
            case '1' :  { addBroker(); break; }
            case '2' :  { break; }
            case '3' :  { break; }
            case '4' :  { brokersInfo(); break; }
            case '5' :  return 0;
        }

    } while (cont);


    return 0;
}

void addBroker() {
    string name;
    cout << "Input broker name : ";
    cin >> name;
    firm.addBroker(name);
    system("clear");
}

void brokersInfo() {
    firm.outputBrokersInfo();
}
