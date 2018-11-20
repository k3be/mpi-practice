#include <stdio.h>
#include <math.h>
#include "mpi.h"

#define PI 3.1415926535

int main(int argc, char **argv) 
{
  // MPI Initialization
  int rank, size;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  long long i, num_intervals;
  double rect_width, area, partial_sum, x_middle, final_sum;

  sscanf(argv[1],"%llu",&num_intervals);

  rect_width = PI / num_intervals;

  long long blocks = num_intervals / size;
  long long start_index = blocks * rank + 1;
  long long end_index = start_index + blocks;

  partial_sum = 0;
  for(i = start_index; i < end_index; i++) {
    // printf("rank: %d, i: %llu\n", rank, i); // debug
    /* find the middle of the interval on the X-axis. */ 

    x_middle = (i - 0.5) * rect_width;
    area = sin(x_middle) * rect_width;
    partial_sum = partial_sum + area;
  }

  if (rank == 0) {
    long long remainder_start_index = blocks * size + 1;
    long long remainder_end_index = num_intervals;
    for(i = remainder_start_index; i < remainder_end_index + 1; i++) {
      // printf("rank: %d, i: %llu\n", rank, i); // debug
      x_middle = (i - 0.5) * rect_width;
      area = sin(x_middle) * rect_width;
      partial_sum = partial_sum + area;
    }
  }

  MPI_Reduce(&partial_sum, &final_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

  if (rank == 0) {
    printf("The total area is: %f\n", (float)final_sum);
  }

  MPI_Finalize();
  return 0;
}   
