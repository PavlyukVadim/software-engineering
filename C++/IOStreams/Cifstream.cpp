#include "Cifstream.h"

Cifstream::Cifstream() { }

Cifstream::Cifstream(string _fileName) {
    fileName = _fileName;
}

void Cifstream::Open() {
    cout << "open file ..." << endl;
    fs.open(fileName, std::fstream::in);
}

void Cifstream::Close() {
    cout << "close file ..." << endl;
    fs.close();
}

Cifstream::~Cifstream() { }
