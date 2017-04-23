#include <iostream>
#include <stack>
#include <string>
#include <cctype>   // для функции isdigit
#include <stdlib.h> // atof
#include <sstream>

using namespace std;


struct Token{
    char ch = ' ';
    double vl = 0;
    bool ischar = false, isdouble = false, isNull = false;
};


void readWhiteSpace(string s, int &pos);
string readDouble(string s, int &pos);
char readFunction(string s, int &pos);
void popFunction(stack<double> &Operands, stack<char> &Functions);
int getPriority(char op);
bool canPop(char op1, stack<char> &Functions);
Token* getToken(string s, int &pos);



double Calc(string s) {
    stack<double> Operands;
    stack<char> Functions;

    int pos = 0;

    s = '(' + s + ')';

    Token *token = new Token;
    Token *prevToken = new Token;

    prevToken->ischar = true;
    prevToken->ch = 'Ы';

    do
    {
        token = getToken(s, pos);
        cout << token->ischar <<  " " << token->ch << endl;
        cout << token->isdouble <<  " " << token->vl << endl << endl;
        // разрливаем унарный + и -
        if (token->ischar && prevToken->ischar &&
            // если эту сточку заменить на (char)prevToken != ')' &&
            // то можно будет писать (2 * -5) или даже (2 - -4)
            // но нужно будет ввести ещё одну проверку так, как запись 2 + -+-+-+2 тоже будет работать :)
            prevToken->ch == '(' &&
            ((token->ch == '+' || token->ch == '-')))
            Operands.push(0); // Добавляем нулевой элемент

        if (token->isdouble) // Если операнд
        {
            Operands.push(token->vl); // то просто кидаем в стек
        }
        // в данном случае у нас только числа и операции. но можно добавить функции, переменные и т.д. и т.п.
        else if (token->ischar) // Если операция
        {
            if (token->ch == ')')
            {
                // Скобка - исключение из правил. выталкивает все операции до первой открывающейся
                while (Functions.size() > 0 && Functions.top() != '(')
                    popFunction(Operands, Functions);
                Functions.pop(); // Удаляем саму скобку "("
            }
            else
            {
                while (canPop(token->ch, Functions)) // Если можно вытолкнуть
                    popFunction(Operands, Functions); // то выталкиваем

                Functions.push(token->ch); // Кидаем новую операцию в стек
            }
        }
        prevToken = token;
    }
    while (!token->isNull);

    if (Operands.size() > 1 || Functions.size() > 0) {
        cout << "Ошибка в разборе выражения";
        return 0;
    }

    double op = Operands.top();
    Operands.pop();
    return op;

}

Token* getToken(string s, int &pos) {
    readWhiteSpace(s, pos);

    Token* token = new Token;

    if (pos == s.length()) { // конец строки
        token->isNull = true;
        return token;
    }
    if (isdigit(s[pos])) {

        double d = 0;
        stringstream ss(readDouble(s, pos));
        ss >> d;
        token->isdouble = true;
        token->vl = d;

        return token;
    }
    else {
        token->ischar = true;
        token->ch = readFunction(s, pos);;
        return token;
    }
}


void popFunction(stack<double> &Operands, stack<char> &Functions) {
    double B = Operands.top();
    Operands.pop();
    double A = Operands.top();
    Operands.pop();


    char func = Functions.top();
    Functions.pop();
    switch (func)
    {
        case '+': Operands.push(A + B);
            break;
        case '-': Operands.push(A - B);
            break;
        case '*': Operands.push(A * B);
            break;
        case '/': Operands.push(A / B);
            break;
    }
    cout << Operands.top() << endl;
}


bool canPop(char op1, stack<char> &Functions) {
    if (Functions.size() == 0)
        return false;
    int p1 = getPriority(op1);
    int p2 = getPriority(Functions.top());

    return p1 >= 0 && p2 >= 0 && p1 >= p2;
}

int getPriority(char op) {
    switch (op)
    {
        case '(':
            return -1; // не выталкивает сам и не дает вытолкнуть себя другим
        case '*': case '/':
            return 1;
        case '+': case '-':
            return 2;
        default:
            cout << "недопустимая операция";
    }
}


string readDouble(string s, int &pos) {
    string res = "";
    while (pos < s.length() && (isdigit(s[pos]) || s[pos] == '.')) {
        res += s[pos++];
    }
    return res;
}

char readFunction(string s, int &pos) {
    // в данном случае все операции состоят из одного символа
    // но мы можем усложнить код добавив == && || mod div и ещё чегонить
    return s[pos++];
}

// Считывает все проблемы и прочие левые символы.
void readWhiteSpace(string s, int &pos) {
    while (pos < s.length() && (s[pos] == ' '))
        pos++;
}



int main ()
{
  double b = Calc("2 + 5 * (2 - 1)");
  cout << b;
  return 0;
}
