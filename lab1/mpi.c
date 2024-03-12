#include "utility.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <mpi.h>

int main(int argc,char **argv) {

  Args ins__args;
  parseArgs(&ins__args, &argc, argv);

  //program input argument
  long inputArgument = ins__args.arg;

  struct timeval ins__tstart, ins__tstop;

  int myrank,nproc;

  MPI_Init(&argc,&argv);

  // obtain my rank
  MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
  // and the number of processes
  MPI_Comm_size(MPI_COMM_WORLD,&nproc);

  if(!myrank)
      gettimeofday(&ins__tstart, NULL);


  // run your computations here (including MPI communication)
  int checker_final = 0;
  int checker = 0; // if 0 it means that number is prime, otherwise not
  long long mine = 2 + myrank;
  for (; mine * mine < inputArgument;) {
    if (inputArgument % mine == 0){
      checker += 1;
      break;
    } 
    mine += nproc;
  }

  MPI_Reduce(&checker, &checker_final, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

  // synchronize/finalize your computations

  if (!myrank) {
    gettimeofday(&ins__tstop, NULL);
    ins__printtime(&ins__tstart, &ins__tstop, ins__args.marker);
    printf("Is prime: %s\n", (checker_final == 0 ? "Yes" : "No"));
  }

  MPI_Finalize();

}
