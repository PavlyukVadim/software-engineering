#include <iostream>
#include <stdio.h>
#include "AlgebraicExpressions.h"

using namespace std;

int main () {

  cout << "Pavlyuk Vadim Ruslanovych" << endl;
  cout << "V : 14" << endl;
  cout << "L : B" << endl << endl;
  bool cont = true;

  do {

    //cin.ignore();
    AlgebraicExpressions a;

    a.setStr();

    AlgebraicExpressions b("2 * 5");

    a = a - b;
    a.getStr();
    double res = a.Calc(5);


    cout << "press Q for exit or other key for restart : ";
    char c = getchar();

    int ch;
	while ((ch = cin.get()) != '\n' && ch != EOF); // flush input

    if (c == 'q') {
        cont = false;
    }

  } while (cont);

  return 0;
}
