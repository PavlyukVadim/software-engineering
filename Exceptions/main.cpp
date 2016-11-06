#include <iostream>
#include "AlgebraicExpressions.h"

using namespace std;

int main () {
  AlgebraicExpressions a("1 + x - 3 * x");

  AlgebraicExpressions b("2 * 5");

  a = a - b;
  //a.getStr();
  double c = a.Calc(5.5555);

  return 0;
}
