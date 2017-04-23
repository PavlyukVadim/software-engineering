#ifndef _DLL_MATRIX_H_
#define _DLL_MATRIX_H_
#include <iostream>
#include <stdlib.h>
#include <time.h>
#if defined DLL_EXPORT
#define DECLDIR __declspec(dllexport)
#else
#define DECLDIR __declspec(dllimport)
#endif
extern "C"
{
    DECLDIR void generateArr(int n, int m, int **arr);
    DECLDIR void countRowSum(int n, int m, int **arr, int* sums);
    DECLDIR void showResult (int n, int m, int **arr, int *sum);
}
#endif
