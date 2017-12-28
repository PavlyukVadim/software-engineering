#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <dirent.h>
#include <sys/stat.h>

#define BLOCK_SIZE 16 // length of each block
#define MAX_DESCRIPTOR_ID 32 // max number of files
#define MAX_LEN_OF_FILE 32

using namespace std;

struct bitmapItem {
    int id;
    bool isFree;
};

struct BlockOfData {
    int id;
    char *data;
};

struct Descriptor {
    int id;
    bool isOpened = false;
    unsigned int size;
    string fileName;
    vector<int> dataId;
};

struct FileLink {
    Descriptor *fileDescriptor;
    string name;
};

struct ControlBlock {
    int numberOfFiles;
    int numberOfBlocks;
    int idOfLastBlock;
    int idOfLastDescriptor;
};

bool mount();
void unmount();

void ls();
void coutDescriptor(Descriptor *fileDescriptor);

Descriptor *create(string fileName); // create file and return descriptor
Descriptor *open(string fileName); // open file for reading and writing
void close(Descriptor *fileDescriptor); // close file

char **read(Descriptor *fileDescriptor, unsigned int offset, unsigned int size); // read size blocks with offset
bool write(Descriptor *fileDescriptor, unsigned int offset, unsigned int size, char **data); // write size blocks with offset

FileLink *link(string filename, string linkname);
void unlink(string linkname);

bool trunkate(string filename, unsigned int newSize); // change file size

Descriptor *getFileDescriptionByName(string fileName);
