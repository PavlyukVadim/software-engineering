# -*- coding: utf-8 -*-
 
def insertionSort(data):
    i = 1;
    while(i < len(data)):
        key = data[i];
        j = i - 1;
        while(j > 0 and data[j] > key):
            data[j + 1] = data[j]
            j -= 1;
        data[j + 1] = key;
        i += 1;
    return data;
    
print(insertionSort([1,5,3,5]))