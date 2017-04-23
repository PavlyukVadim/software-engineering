#include <iostream>

#include "Costream.h"
#include "Cistream.h"
#include "Cifstream.h"

using namespace std;

int main()
{
    Costream cost;
    Cistream cist;

    cost.setData(12);

    cout << "Input int data to istream class: ";
    cin >> cist;

    cout << cost;
    cout << cist.getData() << endl;

    Cifstream fist;
    fist.Open();
    fist.Close();

    return 0;
}
