#include <iostream>
using namespace std;

class Costream
{

    public:
        int data;
        Costream();
        void setData(int data_);
        int getData();
        virtual ~Costream();
        friend ostream &operator<<( ostream &output, const Costream &D ) {
          output << "Output int data: " << D.data << endl;
          return output;
        }

    protected:
    private:

};
