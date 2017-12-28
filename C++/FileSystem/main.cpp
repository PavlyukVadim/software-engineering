#include <iostream>
#include <string.h>
#include "myFileSystem.h"

int main() {

    mount();
    create("file.txt");
    create("file2.txt");

    Descriptor *fileDescriptor = open("file.txt");
    Descriptor *fileDescriptor2 = open("file2.txt");

    char **data = new char*[3];
    data[0] = "1 data";
    data[1] = "2 data";
    data[2] = "3 data";

    write(fileDescriptor, 0, 3, data);
    write(fileDescriptor2, 0, 1, data);

    coutDescriptor(fileDescriptor);

    char **data2 = read(fileDescriptor, 0, 2);
    char **data22 = read(fileDescriptor2, 0, 1);

    cout << "first from file: " << data2[0] << endl;
    cout << "second from file: " << data2[1] << endl;
    cout << "first from file: " << data22[0] << endl;

    coutDescriptor(fileDescriptor);

    trunkate("file.txt", 10);

    ls();

    close(fileDescriptor);
    close(fileDescriptor2);

    unmount();

    return 0;
}
