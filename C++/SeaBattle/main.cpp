#include <iostream>
#include <conio.h>
#include <stdlib.h> // rand()
#include <ctime>
#include "seafight.h"


using namespace std;

int main()
{
    srand( time( 0 ) ); // автоматическая рандомизация
    cout << "Pavlyuk Vadim Ruslanovych" << endl;
    cout << "V : 14" << endl;
    cout << "L : B" << endl << endl;
    bool cont = true;

    do {
        seaFight* s = new seaFight();
        while (s->index1 < 10) {
            s->createShips(1, &(s->index1));
        }

        while (s->index2 < 10) {
            s->createShips(2, &(s->index2));
        }

        s->outputA();

        while (!(s->winner)) {
            s->play();
        }
        cout << "Winner : " << s->winner << endl;

        cout << "press Q for exit or other key for restart : ";
        char c = getch();
        cout << c << endl;
        if (c == 'Q' || c == 'q') {
            cont = false;
        }

        delete s;
    } while (cont);

    return 0;
}
