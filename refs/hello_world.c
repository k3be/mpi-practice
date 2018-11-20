/**
 * Distributed-Memory Programming with MPI #1
 * Compile: mpicc -o mpi1 mpi1.c
 * Execute: mpirun -n 8 ./mpi1
 */

#include "mpi.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Determines the rank of the current process in the communicator‐group MPI_COMM_WORLD
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Determines the size of the communicator‐group MPI_COMM_WORLD
    printf("Hello, World! from %d of %d\n", rank, size);
    MPI_Finalize();
    return 0;
}