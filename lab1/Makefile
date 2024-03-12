MPICC=mpicc
CFLAGS=-O2
LIBS=-lm

ifeq (run,$(firstword $(MAKECMDGOALS)))
  # use the rest as arguments for "run"
  RUN_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  # ...and turn them into do-nothing targets
  $(eval $(RUN_ARGS):;@:)
endif


main: mpi.c
	${MPICC} ${CFLAGS} $< -o mpi ${LIBS}

run:
	mpirun -np 4 ./mpi $(RUN_ARGS)

clean:
	rm mpi