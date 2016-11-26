#include <iostream>
#include <stdio.h>
#include "AlgebraicExpressions.h"
#include "Exception.h"
#include <regex>

#include <signal.h>//-
#include <stdlib.h>//-- for signal
#include <unistd.h>//-


void posix_death_signal(int signum) {
    try{
        throw Exception("Faulty sequence of operators and operands!!!");
    }
    catch (Exception& excection) {
		excection.show();
	}
	exit(3); //выход из программы. Если не сделать этого, то обработчик будет вызываться бесконечно.
}

void signal_callback_handler(int signum) {
   printf("\nCaught signal %d\n",signum);
   if (signum == 2) {
        printf("(Ctrl+^C)\n");
   }
   //exit(signum);
}

using namespace std;

int main () {

  signal(SIGINT, signal_callback_handler);
  //signal(SIGSEGV, posix_death_signal);


  cout << "Pavlyuk Vadim Ruslanovych" << endl;
  cout << "V : 14" << endl;
  cout << "L : B" << endl << endl;
  bool cont = true;
  regex integer("^[0-9x+*-/(). ]+$");

  do {

    AlgebraicExpressions a;
    try {
        a.setStr();
        if(!regex_match(a.str, integer)) throw Exception("Wrong input format!!!");
    }
    catch (Exception& excection) {
		excection.show();
		a.str = "0";
	}

    AlgebraicExpressions b("2 * x");

    a = a - b;
    a.getStr();


    double res = a.Calc(5);
    cout << "Result: " << res << endl;

    cout << "press Q for exit or other key for restart : ";
    char c = getchar();

    int ch;
	while ((ch = cin.get()) != '\n' && ch != EOF); // flush input

    if (c == 'q') {
        cont = false;
    }
    system("clear");

  } while (cont);

  return 0;
}
