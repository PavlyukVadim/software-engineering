#include <iostream>
using namespace std;

class Cistream
{
     public:
        int data;
        Cistream();
        void setData(int data_);
        int getData();
        virtual ~Cistream();
        friend istream &operator>>( istream  &input, Cistream &D ) {
         input >> D.data;
         return input;
      }
};
