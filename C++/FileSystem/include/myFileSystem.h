#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <dirent.h>
#include <sys/stat.h>

#define BLOCKSIZE 16
#define MAX_DESCRIPTOR_ID 32
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


// You need to keep in mind that all sizes ONLY in blocks

bool mount();
void unmount();

string ls();

descriptor* create(string name);
descriptor* open(string name);
void close(descriptor *fd);

char **read(descriptor *fd, unsigned int offset, unsigned int size);
bool write(descriptor *fd, unsigned int offset, unsigned int size, char **data);

filelink *link(string filename, string linkname);
void unlink(string linkname);

bool trunkate(string filename, unsigned int newSize);
