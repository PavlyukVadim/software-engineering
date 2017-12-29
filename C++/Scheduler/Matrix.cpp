#include "Matrix.h"
// private functions
void fill_matrix(matrix_t *matrix, int number);
void swap_rows(matrix_t *matrix, int row1, int row2);
void swap_cols(matrix_t *matrix, int col1, int col2);
bool is_compulsory_task(matrix_t *matrix, int index);
bool is_conflict_task(matrix_t *matrix, int index);
int get_max_rectangular_size(int added_row[], int size, int index_of_added_row);


// implementations
matrix_t* create_matrix(int rows, int cols) {
    matrix_t *matrix = (matrix_t*) malloc(sizeof(matrix_t));
    matrix->cols = cols;
    matrix->rows = rows;
    matrix->table = (int**) malloc (rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matrix->table[i] = (int*) malloc (cols * sizeof(int));
    }
    fill_matrix(matrix, 0);
    return matrix;
}


int destroy_matrix(matrix_t *matrix) {
    if (matrix != NULL) {
        for (int i = 0; i < matrix->rows; i++) {
            free(matrix->table[i]);
        }
        free(matrix->table);
        free(matrix);
        return 1;
    }
    return -1;
}
void print_matrix(matrix_t *matrix) {
    for (int i = 0; i < matrix->rows; ++i) {
        for(int j = 0; j < matrix->cols; ++j) {
            printf("%2d", matrix->table[i][j]);
        }
        printf("\n");
    }
}
void rand_matrix(matrix_t *matrix, int percent) {
    int number = 1;
    int pc = percent;
    if (percent <= 50) {
        fill_matrix(matrix, 0);
        if (percent == 0) return;
    }
    else {
        fill_matrix(matrix, 1);
        if (percent == 100) return;
        number = 0;
        pc = 100 - percent;
    }
    int cells_count = matrix->cols * matrix->rows;
    int numbers_count = cells_count * pc / 100;
    //own formulae to create high variance for my variant
    //to formalize
    int step1 = 245 / pc - 1;
    int step2 = 1;
    if (pc == 50) step1++;
    if (pc <= 35) step1 = 210 / pc;
    if (pc <= 30) step2 = step1/3;
    while (numbers_count) {
        for (int i = rand() % 3; i < cells_count; i += (rand() % step1 + rand() % step2 + 1)) {
            if (matrix->table[i/matrix->rows][i%matrix->cols] != number) {
                matrix->table[i/matrix->rows][i%matrix->cols] = number;
                numbers_count--;
            }
            if (!numbers_count) break;
        }
    }
}

bool solve(matrix_t *matrix, int index) {
    int sum = 0,
        min_sum = -1,
        max_sum = -1,
        min_row = -1,
        max_col = -1;
    for (int row = index; row < matrix->rows; row++) {
        sum = 0;
        for (int col = index; col < matrix->cols; col++) {
            sum += matrix->table[row][col];
        }
        if (min_sum == -1 || sum < min_sum) {
            min_sum = sum;
            min_row = row;
        }
    }
    swap_rows(matrix, index, min_row);
    for (int col = index; col < matrix->cols; col++) {
        if (matrix->table[index][col]) {
            sum = 0;
            for (int row = index; row < matrix->rows; row++) {
                sum += matrix->table[row][col];
            }
            if (max_sum == -1 || max_sum < sum) {
                max_sum = sum; //????
                max_col = col;
            }
        }
    }
    if (max_col != -1) swap_cols(matrix, index, max_col);
    if (is_conflict_task(matrix, 0) && is_compulsory_task(matrix, 0)) {
        return true;
    }
    else if (matrix->rows - 1 == index) {
        return false;
    }
    else {
        return solve(matrix, index + 1);
    }
}

// -----------------------------------------------
bool is_compulsory_task(matrix_t *matrix, int index) {
    for (int row = index; row < matrix->rows; row++) {
        if (!matrix->table[row][row]) return false;
    }

    return true;
}
bool is_conflict_task(matrix_t *matrix, int index) {
    int size = matrix->rows - index;
    int row_[size];
    for (int i = 0; i < size; i++) {
        row_[i] = 0;
    }
    for (int row = index; row < matrix->rows; row++) {
        for (int col = index; col < matrix->cols; col++) {
            if (!matrix->table[row][col]) row_[col-index]++;
            else row_[col-index] = 0;
        }
        if (matrix->rows <= get_max_rectangular_size(row_, size, row))
            return true;
    }
    return false;
}
int get_max_rectangular_size(int added_row[], int size, int index_of_added_row) {
    int max_size = 0;
    int rows = 0;
    int cols = -1;
    int current_max_size = 0;
    for (int i = index_of_added_row; i < size; i++) {
        if (added_row[i] == 0) {
            current_max_size = rows * cols;
            if (current_max_size > max_size) {
                max_size = current_max_size;
            }
            rows = 0;
            cols = -1;
        }
        else {
            if (cols == -1 || cols > added_row[i]) {
                cols = added_row[i];
            }
            rows++;
        }
    }
    current_max_size = rows * cols;
    if (current_max_size > max_size) {
        return current_max_size;
    }
    return max_size;
}
void fill_matrix(matrix_t *matrix, int number) {
    for (int row = 0; row < matrix->rows; row++) {
        for (int col = 0; col < matrix->cols; col++) {
            matrix->table[row][col] = number;
        }
    }
}
void swap_rows(matrix_t *matrix, int row1, int row2) {
    int temp;
    for (int col = 0; col < matrix->cols; col++) {
        temp = matrix->table[row1][col];
        matrix->table[row1][col] = matrix->table[row2][col];
        matrix->table[row2][col] = temp;
    }
}

void swap_cols(matrix_t *matrix, int col1, int col2) {
    int temp;
    for (int row = 0; row < matrix->rows; row++) {
        temp = matrix->table[row][col1];
        matrix->table[row][col1] = matrix->table[row][col2];
        matrix->table[row][col2] = temp;
    }
}
