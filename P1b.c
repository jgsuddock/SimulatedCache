#include <stdio.h>
#include <time.h>
#include <strings.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

#define NbrPlanes 64
#define NbrRows 1024
#define NbrCols 1024

int32_t Data[NbrPlanes][NbrRows][NbrCols];
int32_t Accessed[NbrPlanes][NbrRows][NbrCols];
int32_t NbrPlanesArr[NbrPlanes];
int32_t NbrRowsArr[NbrRows];
int32_t NbrColsArr[NbrCols];

void shuffleArray(int *array, int size) {
	int I;
	for (I = 0; I < size - 1; I++) {
		int temp = I + rand() / (RAND_MAX / (size - I) + 1);
		int t = array[temp];
		array[temp] = array[I];
		array[I] = t;
	}
}

int main (int argc, const char * argv[]) {

	int32_t I, J, K = 0;
	int32_t X = 0;

	printf( ">>CacheBenchmark: Starting.\n");

	for(I = 0; I < NbrPlanes; I++) {
		for(J = 0; J < NbrRows; J++) {
			for(K = 0; K < NbrCols; K++) {
				X = Data[I][J][K];
			}
		}
	}

	sleep(1);

	int32_t* BaseAddr = (int32_t*)(&Data[0][0][0]);
	int32_t* ElementAddr; 
	/*
	printf("Starting Address Traces 1\n");
	FILE *file1 = fopen("AddressTraces1.txt", "wbt");

	for(I = 0; I < NbrPlanes; I++) {
		for(J = 0; J < NbrRows; J++) {
			for(K = 0; K < NbrCols; K++) {
				X = Data[I][J][K];
				ElementAddr = (int32_t*)(&Data[I][J][K] - BaseAddr);
				fwrite(&ElementAddr, 4, 1, file1);
			}
		}
	}
	
	fclose(file1);

	sleep(1);

	printf("Starting Address Traces 2\n");
	FILE *file2 = fopen("AddressTraces2.txt", "wbt");

	for(K = 0; K < NbrCols; K++) {
		for(J = 0; J < NbrRows; J++) {
			for(I = 0; I < NbrPlanes; I++) {
				X = Data[I][J][K];
				ElementAddr = (int32_t*)(&Data[I][J][K] - BaseAddr);
				fwrite(&ElementAddr, 4, 1, file2);
			}
		}
	}

	fclose(file2);

	sleep(1);
	*/
	sleep(1);

	printf("Starting Address Traces 3\n");
	FILE *file3 = fopen("AddressTraces3.txt", "wbt");


	int tempPlanes[NbrPlanes];
	int tempRows[NbrRows];
	int tempCols[NbrCols];

	for(I = 0; I < NbrPlanes; I++) {
		NbrPlanesArr[I] = I;
	}
	for(I = 0; I < NbrRows; I++) {
		NbrRowsArr[I] = I;
	}
	for(I = 0; I < NbrCols; I++) {
		NbrColsArr[I] = I;
	}

	shuffleArray(NbrPlanesArr, NbrPlanes);
	shuffleArray(NbrRowsArr, NbrRows);
	shuffleArray(NbrColsArr, NbrCols);

	for(I = 0; I < NbrPlanes; I++) {
		for(J = 0; J < NbrRows; J++) {
			for(K = 0; K < NbrCols; K++) {
				ElementAddr = (int32_t*)(&Data[NbrPlanesArr[I]][NbrRowsArr[J]][NbrColsArr[K]] - BaseAddr);
				fwrite(&ElementAddr, 4, 1, file3);
			}
		}
	}

	/*
	int32_t ArraySize = NbrPlanes;

	for(I = 0; I < NbrPlanes; I++) {
		int r = rand() % ArraySize;
		int32_t temp[ArraySize--];
		for(J = 0; J < ArraySize; J++) {
			temp[J] = 
		}
		ArraySize--;
	}
	*/

	//std::random_shuffle(&NbrPlanesArr[0],&NbrPlanesArr[NbrPlanes-1]);

	/*
	srand(time(NULL));

	int r1 = rand() % NbrPlanes;

	for(I = 0; I < NbrPlanes; I++) {
		for(J = 0; J < NbrRows; J++) {
			for(K = 0; K < NbrCols; K++) {
				Accessed[r1][r2][r3] = 1;
				ElementAddr = (int32_t*)(&Data[r1][r2][r3] - BaseAddr);
				fwrite(&ElementAddr, 4, 1, file3);
			}
		}
	}
	*/

	//////////////////////////////////////


	return(1);

}
