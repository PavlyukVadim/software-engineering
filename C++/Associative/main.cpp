#include <iostream>
#include "associative.h"
#include <string.h>
#include "Exception.h"

AssociativeArray A;
AssociativeArray B;

void menu (AssociativeArray &K, string name) {

    char a;

    while (true) {

        cout << "Let's work with array " << name << endl;

        cout << "1. Add the key\n";
        cout << "2. Change value\n";
        cout << "3. Delete the key\n";
        cout << "4. Concat two arrays\n";
        cout << "5. Switch array\n";
        cout << "6. Print array\n";
        cout << "7. Quit\n";
        cout << "So? ";

        cin >> a;

        switch (a) {
            case 49: {
                string k;
                cout << "enter the key: ";
                cin >> k;
                K << k;
                break;
            }

            case 50: {

                string k;
                string v;
                cout << "enter the key where is value placed: ";
                cin >> k;
                cout << "enter the new value: ";
                cin >> v;
                try {
                    if(!K.checkExist(K.root, k)) {
                        throw Exception("Unknown key!!!");
                    }
                    K[k] = v;
                }
                catch (Exception& excection) {
                    excection.show();
                }
                break;
            }

            case 51: {

                string k;
                cout << "enter the key: ";
                cin >> k;
                K >> k;
                break;
            }

            case 52: {

                K = A + B;
                break;
            }

            case 53: {

                if (name == "A") {
                    menu(B, "B");
                }

                else {
                    menu(A, "A");
                }
                break;

            }

            case 54: {
                cout << endl;
                K.output(K.root);
                cout << endl;
                getchar();
                getchar();

                break;
            }

            case 55: {

                exit (0);
                break;
            }

            default: break;
        }
    }
}


int main() {


    cout << "We create two arrays to pefrom '+' and '+=' operators\n";
    cout << "1. Work with array A\n";
    cout << "2. Work with array B\n";
    cout << "So? ";


    try {
        char a;
        cin >> a;

        if (a == 49) {
            menu(A, "A");
        }

        else if (a == 50) {
            menu(B, "B");
        }

        else {
            throw Exception("Incorrect input\n");
        }
    }
    catch (Exception& excection) {
		excection.show();
		menu(A, "A"); // default
	}


    return 0;
}
