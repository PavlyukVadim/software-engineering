#include "AlgebraicExpressions.h"
#include "Exception.h"

AlgebraicExpressions::AlgebraicExpressions(string n_str) {
    str = n_str;
}

AlgebraicExpressions AlgebraicExpressions::operator +(AlgebraicExpressions &rv){
    return AlgebraicExpressions("(" + str + ") + (" + rv.str + ")");
}

AlgebraicExpressions AlgebraicExpressions::operator -(AlgebraicExpressions &rv){
    rv.getStr();
    return AlgebraicExpressions("(" + str + ") - (" + rv.str + ")");
}


double AlgebraicExpressions::Calc(double x) {

    stack<double> Operands;
    stack<char> Functions;

    int pos = 0;
    string s = str;

    ostringstream ost;
    ost << x;
    string str_x = ost.str();

    size_t found = 0;
    size_t prev_found = 0;

    while (found < s.size()) {
        found = s.find("x", prev_found);
        if(found >= s.size()) break;
        s = s.substr(0, found) + str_x + s.substr(found + 1);
        prev_found = found + 1;
        cout << s << endl;
    }

    s = '(' + s + ')';

    Token *token = new Token;
    Token *prevToken = new Token;

    prevToken->ischar = true;
    prevToken->ch = 'Ы';

    do
    {
        token = getToken(s, pos);

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


    try {
        if (Operands.size() > 1 || Functions.size() > 0) {
            throw Exception("Ошибка в разборе выражения!!!");
        }
    }
    catch (Exception& excection) {
		excection.show();
		return true;
	}

    double op = Operands.top();
    Operands.pop();
    //cout << op << endl;
    return op;

}

AlgebraicExpressions::Token* AlgebraicExpressions::getToken(string s, int &pos) {
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


void AlgebraicExpressions::popFunction(stack<double> &Operands, stack<char> &Functions) {
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
}


bool AlgebraicExpressions::canPop(char op1, stack<char> &Functions) {
    if (Functions.size() == 0)
        return false;
    int p1 = getPriority(op1);
    int p2 = getPriority(Functions.top());

    return p1 >= 0 && p2 >= 0 && p1 >= p2;
}

int AlgebraicExpressions::getPriority(char op) {
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


string AlgebraicExpressions::readDouble(string s, int &pos) {
    string res = "";
    while (pos < s.length() && (isdigit(s[pos]) || s[pos] == '.')) {
        res += s[pos++];
    }
    return res;
}

char AlgebraicExpressions::readFunction(string s, int &pos) {
    // в данном случае все операции состоят из одного символа
    return s[pos++];
}

// Считывает все проблемы и прочие левые символы.
void AlgebraicExpressions::readWhiteSpace(string s, int &pos) {
    while (pos < s.length() && (s[pos] == ' '))
        pos++;
}
