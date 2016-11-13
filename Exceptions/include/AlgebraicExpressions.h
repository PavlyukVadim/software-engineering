#ifndef ALGEBRAICEXPRESSIONS_H
#define ALGEBRAICEXPRESSIONS_H

#include <string>
#include <iostream>

#include <stack>
#include <string>
#include <cctype>   // для функции isdigit
#include <stdlib.h> // atof
#include <sstream>

using namespace std;

class AlgebraicExpressions
{

    public:

        struct Token{
            char ch = ' ';
            double vl = 0;
            bool ischar = false, isdouble = false, isNull = false;
        };


        string str;
        AlgebraicExpressions() { str = "0";};
        AlgebraicExpressions(string n_str);

        AlgebraicExpressions operator -() const { return AlgebraicExpressions("- (" + str + ")"); };
        AlgebraicExpressions operator +(AlgebraicExpressions &rv);
        AlgebraicExpressions operator -(AlgebraicExpressions &rv);




        void readWhiteSpace(string s, int &pos);
        string readDouble(string s, int &pos);
        char readFunction(string s, int &pos);
        void popFunction(stack<double> &Operands, stack<char> &Functions);
        int getPriority(char op);
        bool canPop(char op1, stack<char> &Functions);
        Token* getToken(string s, int &pos);

        double Calc(double x);

        void getStr() {
            cout << "Expression: " << str << endl;
        }
        void setStr() {
            cout << "Input expression: ";
            getline(cin, str);
            if (!str.length()) {
                str = "0";
            }
        }
};

#endif // ALGEBRAICEXPRESSIONS_H
