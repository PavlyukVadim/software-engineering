#include "myFileSystem.h"

const string filesystemImage = "image.txt";

ofstream file;
ifstream sysFile;

int idOfLastDescriptor = 0;
int idOfLastBlock = 0;

BlockOfData *getBlockOfDataById(int id);
bitmapItem *getBitmapItemById(int id);

vector<Descriptor*> descriptors;
vector<FileLink*> fileLinks;
vector<BlockOfData*> data;
vector<bitmapItem*> bitmap;

ControlBlock controls;

int sizeOfInt = sizeOfInt;
int sizeOfChar = sizeOfChar;
int sizeOfControls = sizeof(controls);



void setDescriptorToFile(Descriptor *desc) {
    int lengthOfName = desc->fileName.size();
    file.write((char*)&lengthOfName, sizeOfInt);
    file.write(desc->fileName.c_str(), desc->fileName.length() * sizeOfChar);
    file.write((char*)&(desc->id), sizeOfInt);
    file.write((char*)&(desc->size), sizeOfInt);
    file.write((char*)&(desc->dataId[0]), sizeOfInt * desc->dataId.size());
}


Descriptor *getDescriptorFromFile() {
    Descriptor *desc = new Descriptor();
    int length;

    sysFile.read((char*)&length, sizeOfInt);
    char *fileName = new char[length];
    sysFile.read(fileName, length * sizeOfChar);
    desc->fileName = string(fileName);

    sysFile.read((char*)&(desc->id), sizeOfInt);
    sysFile.read((char*)&(desc->size), sizeOfInt);

    int *arr = new int[desc->size];
    sysFile.read((char *)&arr[0], sizeOfInt * desc->size);

    for (int i = 0; i < desc->size; i++) {
        desc->dataId.push_back(arr[i]);
        // cout << "data: " << i << " " << arr[i] << endl;
    }
    return desc;
}


void setBlockOfDataToFile(BlockOfData *blockOfData ) {
    file.write((char*)&(blockOfData->id), sizeOfInt);
    file.write(blockOfData->data, sizeOfChar * BLOCK_SIZE);
}


BlockOfData *getBlockOfDataFromFile() {
    BlockOfData *blockOfData = new BlockOfData();
    blockOfData->data = new char[BLOCK_SIZE];
    sysFile.read((char*)&(blockOfData->id), sizeOfInt);
    sysFile.read(blockOfData->data, sizeOfChar * BLOCK_SIZE);
    return blockOfData ;
}


bool mount() {
    sysFile.open(filesystemImage, ios_base::in | ios_base::binary);
    sysFile.read((char*)&controls, sizeOfControls);

    for (int i = 0; i < controls.numberOfFiles; i++) {
        descriptors.push_back(getDescriptorFromFile());
    }

    for (int i = 0; i < controls.numberOfBlocks; i++) {
        bitmapItem *bi;
        sysFile.read((char *)bi, sizeof(bitmapItem));
        bitmap.push_back(bi);
    }

    for (int i = 0; i < controls.numberOfBlocks; i++) {
        data.push_back(getBlockOfDataFromFile());
    }

    idOfLastBlock = controls.idOfLastBlock;
    idOfLastDescriptor = controls.idOfLastDescriptor;

    sysFile.close();
    return true;
}


void clearAll() {
    file.close();

    idOfLastDescriptor = 0;
    idOfLastBlock = 0;

    descriptors.clear();
    links.clear();
    bitmap.clear();
    data.clear();
}


void unmount() {
    file.open(filesystemImage, ios_base::in | ios_base::binary);

    controls.idOfLastBlock = idOfLastBlock;
    controls.idOfLastDescriptor = idOfLastDescriptor;
    controls.numberOfBlocks = bitmap.size();
    controls.numberOfFiles = descriptors.size();

    file.write((char*)&controls, sizeOfControls);

    for (int i = 0; i < controls.numberOfFiles; i++) {
        setDescriptorToFile(descriptors[i]);
    }

    for (int i = 0; i < controls.numberOfBlocks; i++) {
        file.write((char*)bitmap[i], sizeof(bitmapItem));
    }

    for (int i = 0; i < controls.numberOfBlocks; i++) {
        setBlockOfDataToFile(data[i]);
    }

    clearAll();
}


void ls() {
    cout << "fileName"  << " " << "sizeOfFile" << endl;
    for (int i = 0; i < descriptors.size(); i++) {
        string fileName = descriptors[i]->fileName;
        string sizeOfFile = to_string(descriptors[i]->size);
        cout << fileName  << " " << sizeOfFile << endl;
    }
}


Descriptor *open(string fileName) {
    Descriptor *fileDescriptor = getFileDescriptionByName(fileName);
    if (fileDescriptor == NULL) {
        fileDescriptor = new Descriptor();
        fileDescriptor->isOpened = true;
        fileDescriptor->fileName = fileName;
        fileDescriptor->size = 0;
        descriptors.push_back(fileDescriptor);
        return fileDescriptor;
    }
    fileDescriptor->isOpened = true;
    return fileDescriptor;
}


void close(Descriptor *fileDescriptor) {
    fileDescriptor->isOpened = false;
}


Descriptor *create(string fileName) {
    if (idOfLastDescriptor == MAX_DESCRIPTOR_ID) {
        cout << "Warning! Max number of files!" << endl;
        return NULL;
    }

    if (fileName.size() > MAX_LEN_OF_FILE) {
        cout << "Warning! Max number of files!" << endl;
        return NULL;
    }

    Descriptor *fileDescriptor = new Descriptor();
    fileDescriptor->fileName = fileName;
    idOfLastDescriptor += 1;
    fileDescriptor->id = idOfLastDescriptor;
    fileDescriptor->size = 0;

    for (int i = 0; i < descriptors.size(); i++) {
        if (descriptors[i]->fileName == fileName) {
            descriptors[i] = fileDescriptor;
            return fileDescriptor;
        }
    }

    descriptors.push_back(fileDescriptor);
    return fileDescriptor;
}


FileLink *link(string filename, string linkName) {
    FileLink *link = new FileLink();

    for (int i = 0; i < links.size(); i++) {
        if (links[i]->name == linkName) {
            return links[i];
        }
    }

    for (int i = 0; i < descriptors.size(); i++) {
        if (descriptors[i]->fileName == filename) {
            link->name = linkName;
            link->fd = descriptors[i];
            links.push_back(link);
            return link;
        }
    }

    return NULL;
}


void unlink(string linkName) {
    for (int i = 0; i < links.size(); i++) {
        if (links[i]->name == linkName) {
            links.erase(links.begin() + i);
            return;
        }
    }
}


bool trunkate(string filename, unsigned int newSize) {
    Descriptor *fd = getFileDescriptionByName(filename);

    if ((fd == NULL) || (!fd->isOpened)) {
        fd = open(filename);
    }

    if (fd->size > newSize) {
        int delta = fd->size - newSize;

        fd->dataId.erase(fd->dataId.begin() + newSize, fd->dataId.begin() + fd->size + 1);
    } else {

        char **zeroData;
        zeroData = new char*[1];
        zeroData[0] = new char[BLOCK_SIZE];

        for (int i(0); i < BLOCK_SIZE; i++) {
            zeroData[0][i] = '\0';
        }

        int delta = newSize - fd->size;

        for (int i(0); i < delta; i++) {
            int newId = ++idOfLastBlock;

            bitmapItem *newItem = new bitmapItem();

            newItem->id = newId;
            newItem->isFree = true;

            BlockOfData *newBlock = new BlockOfData();

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


char **read(Descriptor *fd, unsigned int offset, unsigned int size) {
    char **buf;
    buf = new char*[size];

    if (offset + size > fd->size) {
        perror("Invalid size");
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        buf[i] = new char[BLOCK_SIZE + 1];
        buf[i][BLOCK_SIZE] = '\0';
    }

    if (fd->isOpened) {
        for (int i(0); i < size; i++) {
            char *data = getBlockOfDataById(fd->dataId[i + offset])->data;
            for (int j = 0; j < BLOCK_SIZE; j++) {
                buf[i][j] = data[j];
            }
        }
        return buf;
    }
    return NULL;
}


bool write(Descriptor *fd, unsigned int offset, unsigned int size, char **dataToWrite) {
    if (fd->isOpened) {
        if (offset + size <= fd->size) {
            for (int i(offset); i < offset + size; i++) {
                getBitmapItemById(fd->dataId[i])->isFree = false;
                getBlockOfDataById(fd->dataId[i])->data = dataToWrite[i - offset];
            }
        } else {
            for (int i(offset); i < fd->size; i++) {
                getBitmapItemById(fd->dataId[i])->isFree = false;
                getBlockOfDataById(fd->dataId[i])->data = dataToWrite[i - offset];
            }

            for (int i(0); i < offset + size - fd->size; i++) {
                BlockOfData *newBlock = new BlockOfData();
                bitmapItem *newBitmapItem = new bitmapItem();

                newBlock->id = ++idOfLastBlock;
                newBlock->data = dataToWrite[i + fd->size];

                newBitmapItem->id = newBlock->id;
                newBitmapItem->isFree = false;

                fd->dataId.push_back(idOfLastBlock);
                bitmap.push_back(newBitmapItem);
                data.push_back(newBlock);
            }
        }
        fd->size = ((offset + size) > fd->size) ? (offset + size) : fd->size;

        return true;
    }

    return false;
}


BlockOfData *getBlockOfDataById(int id) {
    for (int i(0); i < data.size(); i++) {
        if (data[i]->id == id) {
            return data[i];
        }
    }
}


bitmapItem *getBitmapItemById(int id) {
    for (int i(0); i < bitmap.size(); i++) {
        if (bitmap[i]->id == id) {
            return bitmap[i];
        }
    }
}


Descriptor *getFileDescriptionByName(string fileName) {
    for (int i = 0; i < descriptors.size(); i++) {
        if (descriptors[i]->fileName == fileName) {
            return descriptors[i];
        }
    }
    return NULL;
}
