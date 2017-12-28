#include <iostream>
#include <string.h>
#include "myFileSystem.h"

int main() {

    mount();
    create("newFile2.txt");
    Descriptor *fd1 = open("newFile2.txt");
    char **testData = new char*[2];
    testData[0] = "111111111111111";
    testData[1] = "222222222222222";

    write(fd1, 0, 2, testData);
    char **readData = read(fd1, 0, 2);
    trunkate("newFile.txt", 3);
    ls();
    unmount();

    return 0;
}
