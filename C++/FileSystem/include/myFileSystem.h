#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <dirent.h>
#include <sys/stat.h>

#define BLOCKSIZE 16 // length of each block
#define MAX_DESCRIPTOR_ID 32 // max number of files
#define MAX_FILELEN 32

using namespace std;

struct bitmapItem {
    int id;
    bool isFree;
};

struct dataBlock {
    int id;
    char *data;
};

struct descriptor {
    int id;
    bool isOpened = false;
    unsigned int size;
    string name;
    vector<int> dataId;

    descriptor() {
        isOpened = false;
    }
};

struct filelink {
    descriptor *fd;
    string name;
    string filename;
};

struct controlBlock {
    int numberOfBlocks;
    int numberOfFiles;
    int lastBlockId;
    int lastDescriptorId;
};

bool mount();
void unmount();

string ls();

descriptor *create(string name); // create file and return descriptor
descriptor *open(string name); // open file for reading and writing
void close(descriptor *fd); // close file

char **read(descriptor *fd, unsigned int offset, unsigned int size); // read size blocks with offset
bool write(descriptor *fd, unsigned int offset, unsigned int size, char **data); // write size blocks with offset

filelink *link(string filename, string linkname);
void unlink(string linkname);

bool trunkate(string filename, unsigned int newSize); // change file size
