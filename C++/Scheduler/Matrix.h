#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

/******************************************
 * Adjacency matrix for graph             *
 ******************************************/

typedef struct matrix_t {
    int rows;
    int cols;
    int **table;
} matrix_t;


matrix_t* create_matrix(int rows, int cols);

/**
 * Remove created matrix
 * Returns 1 if removed successfulle, else -1
 */
int destroy_matrix(matrix_t *matrix);

/**
 * Prints matrix
 */
void print_matrix(matrix_t *matrix);
void rand_matrix(matrix_t *matrix, int percent);

/**
 * Solves problems for submatrix
 */
bool solve(matrix_t *matrix, int index);
