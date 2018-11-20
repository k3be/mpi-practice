#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mpi.h"

int isprime(int n) {
  int i,squareroot;
  if (n>10) {
    squareroot = (int) sqrt(n);
    for (i=3; i<=squareroot; i=i+2)
      if ((n%i)==0)
        return 0;
    return 1;
  }
  else
    return 0;
}

int main(int argc, char *argv[])
{
  // MPI Initialization
  int rank, size;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int partial_pc,       /* prime counter */
      final_pc,
      final_foundone,
      partial_foundone = 0; /* most recent prime found */
  long long int n, limit;

  sscanf(argv[1],"%llu",&limit);	
  if (rank == 0) {
    printf("Starting. Numbers to be scanned= %lld\n",limit);
  }

  long long blocks = limit / size;
  long long start_index = blocks * rank;
  long long end_index = start_index + blocks - 1;
  if (start_index < 11) {
    start_index = 11;
  }
  if (start_index % 2 == 0) {
    start_index++;
  }

  partial_pc=0;     /* Assume (2,3,5,7) aren't counted here */
  for (n=start_index; n<=end_index; n=n+2) {
    // printf("rank: %d, n: %llu\n", rank, n); // debug
    if (isprime(n)) {
      partial_pc++;
      partial_foundone = n;
    }			
  }

  if (rank == 0) {
    long long remainder_start_index = blocks * size;
    long long remainder_end_index = limit;
    if (remainder_start_index % 2 == 0) {
      remainder_start_index++;
    }
    for (n=remainder_start_index; n<=remainder_end_index; n=n+2) {
      // printf("rank: %d, n: %llu\n", rank, n); // debug
      if (isprime(n)) {
        partial_pc++;
        partial_foundone = n;
      }
    }
  }

  MPI_Reduce(&partial_pc, &final_pc, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
  MPI_Reduce(&partial_foundone, &final_foundone, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

  if (rank == 0) {
    final_pc += 4;
    printf("Done. Largest prime is %d Total primes %d\n",final_foundone,final_pc);
  }

  MPI_Finalize();
  return 0;
} 
