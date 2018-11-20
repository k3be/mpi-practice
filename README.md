# mpi-practice

- prime.c
    - takes a long long int argument as an input, finds the largest prime number that is smaller than the input, and counts the prime numbers that are smaller than the input.
- integrate.c
    -  integrates function sin(X) over the range from 0 to π using N intervals, where N is an argument of the program.

## Run

```bash
/usr/lib64/openmpi/bin/mpicc -o prime prime.c -lm
/usr/lib64/openmpi/bin/mpiexec -n 4 -hostfile hostfile ./prime 123456

/usr/lib64/openmpi/bin/mpicc -o integrate integrate.c -lm
/usr/lib64/openmpi/bin/mpiexec -n 4 -hostfile hostfile ./integrate 123456
```

## Sample hostfile

```
6.6.6.6
example.com
i.need.a.break
```