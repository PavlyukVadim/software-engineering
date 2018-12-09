#include <stdio.h>
#include <mpi.h>

/* Matrix size and process number */
#define MAT_SIZE 4
#define PROCS 2

int main(int argc, char *argv[]) {
    int size, rank;

    const int width = MAT_SIZE / PROCS;

    int src_mat[MAT_SIZE * width];
    int des_mat[MAT_SIZE * width];

    /*
     * Initialize MPI and get rank number of this
     * process and total number of processes.
     */
    MPI_Init (&argc, &argv);
    MPI_Comm_size (MPI_COMM_WORLD, &size);
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);

    /* Check if process number is PROC_NUM, that is, 2 */
    if (size != PROCS) {
        if (rank == 0) {
            printf ("Run with option 'mpirun -np %d'!", PROCS);
        }
        MPI_Finalize ();
        return 1;
    }


    printf("Initial matrix: \n");
    /* Initialize values in the matrix */
    for (int i = 0; i < MAT_SIZE; i++) {
        for (int j = 0; j < width; j++) {
            src_mat[i * width + j] = i * MAT_SIZE + (rank * width + j);
            printf("%d ", src_mat[i * width + j]);
        }
        printf("\n");
    }


    /*
     * Here in this process we send data blocks to
     * all processes in MPI_COMM_WORLD. And we'll
     * receive date blocks from all processes as well.
     */
    MPI_Alltoall(src_mat, width * width, MPI_INT,
                 des_mat, width * width, MPI_INT, MPI_COMM_WORLD);


    printf("send data: \n");
    for (int i = 0; i < MAT_SIZE; i++) {
        for (int j = 0; j < width; j++) {
            printf("%d ", des_mat[i * width + j]);
        }
        printf("\n");
    }
    printf("\n");

    /*
     * After get data blocks from other processes,
     * it's time to transpose each of them (each
     * block is a sub-matrix).
     */
    for (int i = 0; i < PROCS; i++)
        for (int j = 0; j < width; j++)
            for (int k = 0; k < j; k++) {
                int exch_1 = (i * width + j) * width + k;
                int exch_2 = (i * width + k) * width + j;
                printf("Exches: %d %d", exch_1, exch_2);
                printf("\n");
                int temp = des_mat[exch_1];
                des_mat[exch_1] = des_mat[exch_2];
                des_mat[exch_2] = temp;

                printf("changes data: \n");
                for (int i1 = 0; i1 < MAT_SIZE; i1++) {
                    for (int j1 = 0; j1 < width; j1++) {
                        printf("%d ", des_mat[i1 * width + j1]);
                    }
                    printf("\n");
                }
            }

    /*
     * Check whether the result is right in every
     */


    for (int i = 0; i < MAT_SIZE; i++) {
        for (int j = 0; j < width; j++) {
            /*
             * element in [i][j] should be from [j][i] originally
             * then column turns to be rank * width + j.
             */
            if (des_mat[i * width + j] != MAT_SIZE * (rank * width + j) + i) {
                printf("Element wrong.\n");
                MPI_Abort(MPI_COMM_WORLD, 1);
                return 1;
            }
        }
    }

    /* If no problem, then the first process prints result out */
    if (rank == 0) {
        printf ("Result correct.\n");
    }

    MPI_Finalize ();

    printf("result: \n");
    for (int i = 0; i < MAT_SIZE; i++) {
        for (int j = 0; j < width; j++) {
            printf("%d ", des_mat[i * width + j]);
        }
        printf("\n");
    }

    return 0;
}
