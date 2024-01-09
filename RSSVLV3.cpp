#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>
int main(int argc, char* argv[]) {
	int rang;
	int matProc = 0;
	double param[2];
	param[0] = 0;
	param[1] = 0;
	const int MAKS_BROJ = 10;
	double abc[MAKS_BROJ];
	
	MPI_Init(&argc, &argv);
	for (int a = 0; a < 10; a = a + 1)
	{
		abc[a] = 1.0 + a;
	}
	int velicina;
	MPI_Comm_size(MPI_COMM_WORLD, &velicina);
	printf("P%d: prije broadcastani parametri su %f i %f\n", rang, param[0], param[1]);
	MPI_Barrier(MPI_COMM_WORLD);
	if (velicina < 2) {
		return 0;
	}
	MPI_Comm_rank(MPI_COMM_WORLD, &rang);
	if (rang == matProc) { 
		param[0] = abc[8]; param[1] = abc[9];
	}
	MPI_Bcast(&param, 2, MPI_DOUBLE, matProc, MPI_COMM_WORLD); //broadcast parametra
	printf("P%d: poslije broadcastani parametri su %f i %f\n", rang, param[0], param[1]);
MPI_Finalize();
	return 0;
}