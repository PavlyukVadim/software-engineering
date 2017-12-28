#include "myFileSystem.h"

const string fileSystemStore = "store.txt";

ofstream file;
ifstream storeFile;

int idOfLastDescriptor = 0;
int idOfLastBlock = 0;

BlockOfData *getBlockOfDataById(int id);
bitmapItem *getBitmapItemById(int id);

vector<Descriptor*> descriptors;
vector<FileLink*> fileLinks;
vector<BlockOfData*> blocksOfData;
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

    storeFile.read((char*)&length, sizeOfInt);
    char *fileName = new char[length];
    storeFile.read(fileName, length * sizeOfChar);
    desc->fileName = string(fileName);

    storeFile.read((char*)&(desc->id), sizeOfInt);
    storeFile.read((char*)&(desc->size), sizeOfInt);

    int *arr = new int[desc->size];
    storeFile.read((char *)&arr[0], sizeOfInt * desc->size);

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
    storeFile.read((char*)&(blockOfData->id), sizeOfInt);
    storeFile.read(blockOfData->data, sizeOfChar * BLOCK_SIZE);
    return blockOfData;
}


bool mount() {
    storeFile.open(fileSystemStore, ios_base::in | ios_base::binary);
    storeFile.read((char*)&controls, sizeOfControls);

    for (int i = 0; i < controls.numberOfFiles; i++) {
        descriptors.push_back(getDescriptorFromFile());
    }

    for (int i = 0; i < controls.numberOfBlocks; i++) {
        bitmapItem *bi;
        storeFile.read((char *)bi, sizeof(bitmapItem));
        bitmap.push_back(bi);
    }

    for (int i = 0; i < controls.numberOfBlocks; i++) {
        blocksOfData.push_back(getBlockOfDataFromFile());
    }

    idOfLastBlock = controls.idOfLastBlock;
    idOfLastDescriptor = controls.idOfLastDescriptor;

    storeFile.close();
    return true;
}


void clearAll() {
    file.close();

    idOfLastDescriptor = 0;
    idOfLastBlock = 0;

    descriptors.clear();
    fileLinks.clear();
    bitmap.clear();
    blocksOfData.clear();
}


void unmount() {
    file.open(fileSystemStore, ios_base::in | ios_base::binary);

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
        setBlockOfDataToFile(blocksOfData[i]);
    }

    clearAll();
}


void ls() {
    cout << endl << "ls: " << endl;
    cout << "fileName"  << " " << "sizeOfFile" << endl;
    for (int i = 0; i < descriptors.size(); i++) {
        string fileName = descriptors[i]->fileName;
        string sizeOfFile = to_string(descriptors[i]->size);
        cout << fileName  << " " << sizeOfFile << endl;
    }
    cout << endl;
}


void coutDescriptor(Descriptor *fileDescriptor) {
    cout << endl;
    cout << "id: " << fileDescriptor->id << endl;
    cout << "fileName: " << fileDescriptor->fileName << endl;
    cout << "isOpened: " << fileDescriptor->isOpened << endl;
    cout << "size: " << fileDescriptor->size << endl;
    cout << endl;
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


FileLink *link(string fileName, string linkName) {
    FileLink *fileLink = new FileLink();

    for (int i = 0; i < fileLinks.size(); i++) {
        if (fileLinks[i]->name == linkName) {
            return fileLinks[i];
        }
    }

    for (int i = 0; i < descriptors.size(); i++) {
        if (descriptors[i]->fileName == fileName) {
            fileLink->name = linkName;
            fileLink->fileDescriptor = descriptors[i];
            fileLinks.push_back(fileLink);
            return fileLink;
        }
    }

    return NULL;
}


void unlink(string linkName) {
    for (int i = 0; i < fileLinks.size(); i++) {
        if (fileLinks[i]->name == linkName) {
            fileLinks.erase(fileLinks.begin() + i);
            return;
        }
    }
}


bool trunkate(string fileName, unsigned int newSize) {
    Descriptor *fileDescriptor = getFileDescriptionByName(fileName);

    if ((fileDescriptor == NULL) || (!fileDescriptor->isOpened)) {
        fileDescriptor = open(fileName);
    }

    if (fileDescriptor->size > newSize) {
        // erase the rest
        fileDescriptor->dataId.erase(
            fileDescriptor->dataId.begin() + newSize,
            fileDescriptor->dataId.begin() + fileDescriptor->size + 1
        );
    } else {
        char **zeroData;
        zeroData = new char*[1];
        zeroData[0] = new char[BLOCK_SIZE];

        for (int i = 0; i < BLOCK_SIZE; i++) {
            zeroData[0][i] = '\0';
        }

        int delta = newSize - fileDescriptor->size;
        for (int i = 0; i < delta; i++) {
            idOfLastBlock += 1;
            int newId = idOfLastBlock;

            bitmapItem *newItem = new bitmapItem();

            newItem->id = newId;
            newItem->isFree = true;

            BlockOfData *newBlock = new BlockOfData();

            newBlock->id = newId;
            newBlock->data = zeroData[0];

            fileDescriptor->dataId.push_back(newId);
            bitmap.push_back(newItem);
            blocksOfData.push_back(newBlock);
        }
        fileDescriptor->size = newSize;
        delete zeroData[0];
        delete zeroData;
    }
    return false;
}


char **read(Descriptor *fileDescriptor, unsigned int offset, unsigned int size) {
    char **buf;
    buf = new char*[size];

    if (offset + size > fileDescriptor->size) {
        cout << "Invalid size" << endl;
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        buf[i] = new char[BLOCK_SIZE + 1];
        buf[i][BLOCK_SIZE] = '\0';
    }

    if (fileDescriptor->isOpened) {
        for (int i = 0; i < size; i++) {
            char *data = getBlockOfDataById(fileDescriptor->dataId[i + offset])->data;
            for (int j = 0; j < BLOCK_SIZE; j++) {
                buf[i][j] = data[j];
            }
        }
        return buf;
    }
    return NULL;
}


bool write(Descriptor *fileDescriptor, unsigned int offset, unsigned int size, char **dataToWrite) {
    if (fileDescriptor->isOpened) {
        if (offset + size <= fileDescriptor->size) {
            for (int i = offset; i < offset + size; i++) {
                getBitmapItemById(fileDescriptor->dataId[i])->isFree = false;
                getBlockOfDataById(fileDescriptor->dataId[i])->data = dataToWrite[i - offset];
            }
        } else {
            for (int i = offset; i < fileDescriptor->size; i++) {
                getBitmapItemById(fileDescriptor->dataId[i])->isFree = false;
                getBlockOfDataById(fileDescriptor->dataId[i])->data = dataToWrite[i - offset];
            }

            for (int i = 0; i < offset + size - fileDescriptor->size; i++) {
                BlockOfData *newBlock = new BlockOfData();
                bitmapItem *newBitmapItem = new bitmapItem();

                idOfLastBlock += 1;

                newBlock->id = idOfLastBlock;
                newBlock->data = dataToWrite[i + fileDescriptor->size];

                newBitmapItem->id = newBlock->id;
                newBitmapItem->isFree = false;

                fileDescriptor->dataId.push_back(idOfLastBlock);
                bitmap.push_back(newBitmapItem);
                blocksOfData.push_back(newBlock);
            }
            fileDescriptor->size = offset + size;
        }
        return true;
    }
    return false;
}


BlockOfData *getBlockOfDataById(int id) {
    for (int i = 0; i < blocksOfData.size(); i++) {
        if (blocksOfData[i]->id == id) {
            return blocksOfData[i];
        }
    }
}


bitmapItem *getBitmapItemById(int id) {
    for (int i = 0; i < bitmap.size(); i++) {
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
