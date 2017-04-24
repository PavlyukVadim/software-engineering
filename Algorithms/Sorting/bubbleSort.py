# -*- coding: utf-8 -*-

def bubbleSort(arr):
    
    ordered = 0;
    while (ordered < len(arr)):    
        i = 0;
        while (i < len(arr) - 1 - ordered):
            if(arr[i] > arr[i + 1]):
                arr[i], arr[i + 1] = arr[i + 1], arr[i];        
            i += 1;
        ordered += 1;
    return arr;
    
print(bubbleSort([11,7,3,4]))