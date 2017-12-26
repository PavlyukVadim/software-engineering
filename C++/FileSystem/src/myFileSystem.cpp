#include "myFileSystem.h"

const string filesystemImage = "image.txt";
string root;


const char *fileRoot;

ofstream file;
ifstream sysFile;

int lastDescriptorId = 0;
int lastBlockId = 0;

controlBlock controls;

descriptor *getFileDescr(string name);
dataBlock *getDataBlockById(int id);
bitmapItem *getBitmapItemById(int id);

vector<descriptor*> descriptors;
vector<filelink*> links;
vector<dataBlock*> data;
vector<bitmapItem*> bitmap;


void writeDescriptorToFile(descriptor *desc) {
    int len = desc->name.size();

    file.write((char *)&len, sizeof(int));
    file.write(desc->name.c_str(), desc->name.length() * sizeof(char));
    file.write((char *)&(desc->id), sizeof(int));
    file.write((char *)&(desc->size), sizeof(int));
    file.write((char *)&(desc->dataId[0]), sizeof(int) * desc->dataId.size());
}

descriptor* readDescriptorFromFile() {
    descriptor *desc = new descriptor();
    char *name;
    int len;

    sysFile.read((char *)&len, sizeof(int));

    name = new char[len];

    sysFile.read(name, len * sizeof(char));

    string tmp(name);
    desc->name = tmp;
    sysFile.read((char *)&(desc->id), sizeof(int));

    sysFile.read((char *)&(desc->size), sizeof(int));

    int *arr = new int[desc->size];
    sysFile.read((char *)&arr[0], sizeof(int) * desc->size);

    for (int i(0); i < desc->size; i++) {
        desc->dataId.push_back(arr[i]);
    }

    return desc;
}

void writeDataItemToFile(dataBlock *item) {
    file.write((char *)&(item->id), sizeof(int));
    file.write(item->data, sizeof(char) * BLOCKSIZE);
}

dataBlock* readDataItemFromFile() {
    dataBlock *item = new dataBlock();

    item->data = new char[BLOCKSIZE];
    sysFile.read((char *)&(item->id), sizeof(int));
    sysFile.read(item->data, sizeof(char) * BLOCKSIZE);

    return item;
}

bool mount() {
    sysFile.open("image.txt", ios_base::in | ios_base::binary);

    sysFile.read((char *)&controls, sizeof(controls));

    for (int i(0); i < controls.numberOfFiles; i++) {
        descriptors.push_back(readDescriptorFromFile());
    }

    for (int i(0); i < controls.numberOfBlocks; i++) {
        bitmapItem *bi;
        sysFile.read((char *)bi, sizeof(bitmapItem));
        bitmap.push_back(bi);
    }

    for (int i(0); i < controls.numberOfBlocks; i++) {
        data.push_back(readDataItemFromFile());
    }

    lastBlockId = controls.lastBlockId;
    lastDescriptorId = controls.lastDescriptorId;

    sysFile.close();

    return true;
}

void unmount() {
    file.open("image.txt", ios_base::in | ios_base::binary);

    controls.lastBlockId = lastBlockId;
    controls.lastDescriptorId = lastDescriptorId;
    controls.numberOfBlocks = bitmap.size();
    controls.numberOfFiles = descriptors.size();

    file.write((char *)&controls, sizeof(controls));

    for (int i(0); i < controls.numberOfFiles; i++) {
        writeDescriptorToFile(descriptors[i]);
    }

    for (int i(0); i < controls.numberOfBlocks; i++) {
        file.write((char *)bitmap[i], sizeof(bitmapItem));
    }

    for (int i(0); i < controls.numberOfBlocks; i++) {
        writeDataItemToFile(data[i]);
    }

    file.close();

    descriptors.clear();
    links.clear();
    bitmap.clear();
    data.clear();

    lastDescriptorId = 0;
    lastBlockId = 0;
}


string ls() {
    string res = "";

    for (int i(0); i < descriptors.size(); i++) {
        res += descriptors[i]->name + "\n";
    }

    cout << res << endl;

    return res;
}

descriptor* open(string name) {
    descriptor *fd = getFileDescr(name);

    if (fd == NULL) {
        fd = new descriptor();
        fd->isOpened = true;
        fd->name = name;

        fd->size = 0;

        fd->size = 0;

        descriptors.push_back(fd);

        return fd;
    }

    fd->isOpened = true;

    return fd;
}

void close(descriptor *fd) {
    fd->isOpened = false;
}

descriptor* create(string name) {

    if (lastDescriptorId == MAX_DESCRIPTOR_ID) {
        perror("Max number of files!");

        return NULL;
    }

    if (name.size() > MAX_FILELEN) {
        perror("Too long name!");

        return NULL;
    }

    descriptor *fd = new descriptor();
    fd->name = name;
    fd->id = ++lastDescriptorId;

    fd->size = 0;

    for (int i(0); i < descriptors.size(); i++) {
        if (descriptors[i]->name == name) {
            descriptors[i] = fd;

            return fd;
        }
    }

    descriptors.push_back(fd);

    return fd;
}
filelink* link(string filename, string linkname) {
    filelink* link = new filelink();

    for (int i(0); i < links.size(); i++) {
        if (links[i]->name == linkname) {
            return links[i];
        }
    }


    for (int i(0); i < descriptors.size(); i++) {
        if (descriptors[i]->name == filename) {

            link->name = linkname;
            link->fd = descriptors[i];

            links.push_back(link);

            return link;
        }
    }

    return NULL;
}
void unlink(string linkname) {
    for (int i(0); i < links.size(); i++) {
        if (links[i]->name == linkname) {
            links.erase(links.begin() + i);

            return;
        }
    }
}


bool trunkate(string filename, unsigned int newSize) {
    descriptor *fd = getFileDescr(filename);

    if ((fd == NULL) || (!fd->isOpened)) {
        fd = open(filename);
    }

    if (fd->size > newSize) {
        int delta = fd->size - newSize;

        fd->dataId.erase(fd->dataId.begin() + newSize, fd->dataId.begin() + fd->size + 1);
    } else {

        char **zeroData;
        zeroData = new char*[1];
        zeroData[0] = new char[BLOCKSIZE];

        for (int i(0); i < BLOCKSIZE; i++) {
            zeroData[0][i] = '\0';
        }

        int delta = newSize - fd->size;

        for (int i(0); i < delta; i++) {
            int newId = ++lastBlockId;

            bitmapItem *newItem = new bitmapItem();

            newItem->id = newId;
            newItem->isFree = true;

            dataBlock *newBlock = new dataBlock();

            newBlock->id = newId;
            newBlock->data = zeroData[0];

            fd->dataId.push_back(newId);
            bitmap.push_back(newItem);
            data.push_back(newBlock);
        }

        fd->size = newSize;

        delete zeroData[0];
        delete zeroData;
    }

    return false;
}



char **read(descriptor *fd, unsigned int offset, unsigned int size) {
    char **buf;
    buf = new char*[size];

    if (offset + size > fd->size) {
        perror("Invalid size");

        return NULL;
    }

    for (int i(0); i < size; i++) {
        buf[i] = new char[BLOCKSIZE + 1];
        buf[i][BLOCKSIZE] = '\0';
    }

    if (fd->isOpened) {
        for (int i(0); i < size; i++) {
            char *data = getDataBlockById(fd->dataId[i + offset])->data;
            for (int j(0); j < BLOCKSIZE; j++) {
                buf[i][j] = data[j];
            }
        }

        return buf;
    }

    return NULL;
}



bool write(descriptor *fd, unsigned int offset, unsigned int size, char **dataToWrite) {

    if (fd->isOpened) {
        if (offset + size <= fd->size) {
            for (int i(offset); i < offset + size; i++) {
                getBitmapItemById(fd->dataId[i])->isFree = false;
                getDataBlockById(fd->dataId[i])->data = dataToWrite[i - offset];
            }
        } else {
            for (int i(offset); i < fd->size; i++) {
                getBitmapItemById(fd->dataId[i])->isFree = false;
                getDataBlockById(fd->dataId[i])->data = dataToWrite[i - offset];
            }

            for (int i(0); i < offset + size - fd->size; i++) {
                dataBlock *newBlock = new dataBlock();
                bitmapItem *newBitmapItem = new bitmapItem();

                newBlock->id = ++lastBlockId;
                newBlock->data = dataToWrite[i + fd->size];

                newBitmapItem->id = newBlock->id;
                newBitmapItem->isFree = false;

                fd->dataId.push_back(lastBlockId);
                bitmap.push_back(newBitmapItem);
                data.push_back(newBlock);
            }
        }
        fd->size = ((offset + size) > fd->size) ? (offset + size) : fd->size;

        return true;
    }

    return false;
}


dataBlock* getDataBlockById(int id) {
    for (int i(0); i < data.size(); i++) {
        if (data[i]->id == id) {
            return data[i];
        }
    }
}

bitmapItem* getBitmapItemById(int id) {
    for (int i(0); i < bitmap.size(); i++) {
        if (bitmap[i]->id == id) {
            return bitmap[i];
        }
    }
}

descriptor *getFileDescr(string name) {
    for (int i(0); i < descriptors.size(); i++) {
        if (descriptors[i]->name == name) {
            return descriptors[i];
        }
    }

    return NULL;
}
