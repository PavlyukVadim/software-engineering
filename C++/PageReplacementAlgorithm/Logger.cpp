#include "Logger.h"

using namespace std;

Logger::~Logger() {
    outFile.close();
}

void Logger::writeToFile(string str) {
    outFile << str;
}
