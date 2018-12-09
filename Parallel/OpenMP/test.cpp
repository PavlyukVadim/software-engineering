//
// Created by Pavliuk Vadym on 2018-12-09.
//


/******************************************************************************
   Example 14   :        Omp_MatrixTranspose.c

   Objective    : Write an OpenMP Program for Transpose of a Matrix
                  and measure the performance
                  This example demonstrates the use of
                  PARALLEL Directive and Private clause

   Input        : Size of matrices (numofrows and noofcols )

   Output       : Each thread transposes assaigned Row and finally
                  master prints the final resultant matrix

******************************************************************************/

#include <stdio.h>
#include <sys/time.h>
#include <omp.h>
#include <cstdlib>
//#include <cstdlib>

//#include <stdlib.h> // for malloc and free
//void* operator new(size_t size) { return malloc(size); }
//void operator delete(void* ptr) { free(ptr); }

/* Main Program */

int main(int argc, char *argv[]) {
    int NoofRows = 4, NoofCols = 4, i, j;
    int **Matrix, **Trans, **Checkoutput;
    float flops;

    struct timeval  TimeValue_Start;
    struct timezone TimeZone_Start;

    struct timeval  TimeValue_Final;
    struct timezone TimeZone_Final;
    long            time_start, time_end, time_overhead;

//    printf("Read The Matrix Size Noofrows And Colums Of Matrix \n");
//    scanf("%d%d", &NoofRows, &NoofCols);

    if (NoofRows <= 0 || NoofCols <= 0) {
        printf("The NoofRows And NoofCols Should Be Of Positive Sign\n");
        exit(1);
    }
    /* Matrix Elements */

    Matrix = new int*[NoofRows];

    for (i = 0; i < NoofRows; i++) {
        Matrix[i] = new int[NoofCols];
//                (float *) malloc(sizeof(float) * (NoofCols) - 1);
        for (j = 0; j < NoofCols; j++)
            Matrix[i][j] = (i * j) * 5 + i;
    }

    printf("The Input Matrix Is \n");

    for (i = 0; i < NoofRows; i++) {
        for (j = 0; j < NoofCols; j++)
            printf("%d \t", Matrix[i][j]);
        printf("\n");
    }

    /* Dynamic Memory Allocation */

    Trans = new int*[NoofRows];
    Checkoutput = new int*[NoofRows];

    /* Initializing The Output Matrices Elements As Zero */

    for (i = 0; i < NoofCols; i++) {
        Checkoutput[i] = new int[NoofCols];
        Trans[i] = new int[NoofCols];
        for (j = 0; j < NoofRows; j++) {
            Checkoutput[i][j] = 0.0;
            Trans[i][j] = 0.0;
        }
    }

    gettimeofday(&TimeValue_Start, &TimeZone_Start);

    /* OpenMP Parallel For Directive */

#pragma omp parallel for private(j)
    for (i = 0; i < NoofRows; i = i + 1)
        for (j = 0; j < NoofCols; j = j + 1)
            Trans[j][i] = Matrix[i][j];

    gettimeofday(&TimeValue_Final, &TimeZone_Final);

    time_start = TimeValue_Start.tv_sec * 1000000 + TimeValue_Start.tv_usec;
    time_end = TimeValue_Final.tv_sec * 1000000 + TimeValue_Final.tv_usec;
    time_overhead = time_end - time_start;


    /* Serial Computation */

    for (i = 0; i < NoofRows; i = i + 1)
        for (j = 0; j < NoofCols; j = j + 1)
            Checkoutput[j][i] = Matrix[i][j];

    for (i = 0; i < NoofCols; i = i + 1)
        for (j = 0; j < NoofRows; j = j + 1)
            if (Checkoutput[i][j] == Trans[i][j])
                continue;
            else {
                printf("There Is A Difference From Serial And Parallel Calculation \n");
//                exit(1);
            }

    printf("\nTime Overhead = %ld\n", time_overhead);

    printf("The Input Matrix Is \n");

    for (i = 0; i < NoofRows; i++) {
        for (j = 0; j < NoofCols; j++)
            printf("%d \t", Matrix[i][j]);
        printf("\n");
    }

    printf("\nThe Transpose Matrix Is \n");
    for (i = 0; i < NoofCols; i = i + 1) {
        for (j = 0; j < NoofRows; j = j + 1)
            printf("%d \t", Trans[i][j]);
        printf("\n");
    }

    /* Calculation Of Flops */

    flops = (float) 2 *NoofRows * NoofCols / (float) time_overhead;
    printf("\nNoofRows=%d\t NoofCols=%d \t Flops=%fMFlops\n", NoofRows, NoofCols, flops);

    /* Freeing Allocated Memory */

//    for (i = 0; i < NoofRows; i++) {
//        delete Matrix[i];
//        delete Checkoutput[i];
//        delete Trans[i];
//    }
//
//    delete[] Matrix;
//    delete[] Checkoutput;
//    delete[] Trans;

//    free(Matrix);
//    free(Checkoutput);
//    free(Trans);

}