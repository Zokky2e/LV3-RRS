#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>
int main(int argc, char* argv[]) {
	int rang;
	int matProc = 0;
	double mnoz = 7;
	int moj;
	const int MAKS_BROJ = 10;
	int abc[MAKS_BROJ];
	int rezultat[MAKS_BROJ];
	int rez;
	int finalRezu = 0;
	int kol_poslanih, kol_primljenih;

	int velicina;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &velicina);
	if (velicina < 2) {
		return 0;
	}
	MPI_Comm_rank(MPI_COMM_WORLD, &rang);
	kol_primljenih = 1;
	if (rang == matProc) {
		for (int i = 0; i < 10; i++) {
			abc[i] = i+1; // maticni proces popunjava polje param[8]
			printf("P%d: param[%d] = %d\n", rang, i, abc[i]);
		}
		kol_poslanih = 1; // koliko podataka ce maticni proces poslati svakom procesu
	}
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Scatter(
		abc, kol_poslanih, 
		MPI_INT, &moj, kol_primljenih,
		MPI_INT, matProc, MPI_COMM_WORLD
	);

			rez = moj * mnoz;
			//abc[rang] = rez;
			printf("P%d: moj broj je %d i pomnozen iznosi %f\n", rang,moj, moj * mnoz);

	MPI_Gather(&rez,
		1,
		MPI_INT,
		abc,
		1,
		MPI_INT,
		matProc,
		MPI_COMM_WORLD
	);
	if (matProc == rang)
	{
		for (int i = 0; i < 10; i++) {

			printf("param[%d] = %d\n", i, abc[i]);
			finalRezu += abc[i];
		}
		printf("P%d: rezultat redukcije pomocu MPI_SUM je %d\n", rang, finalRezu / 10);
	}
	MPI_Finalize();

	return 0;
}

// P0: [1,2]
// P1: [2,3]

// [3, 5]