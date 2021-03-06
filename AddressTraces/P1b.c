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

/*
 * Used in random address trace
 */
void shuffleArray(int *array, int size) {
	int I;
	//Shuffles the array into a random order
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

	//Defining and initializing base address
	int32_t* BaseAddr = (int32_t*)(&Data[0][0][0]);
	int32_t* ElementAddr; 
	
	printf("Starting Address Trace 1\n");
	// Create/open file
	FILE *file1 = fopen("AddressTraces1.txt", "wbt");

	for(I = 0; I < NbrPlanes; I++) {
		for(J = 0; J < NbrRows; J++) {
			for(K = 0; K < NbrCols; K++) {
				X = Data[I][J][K];
				ElementAddr = (int32_t*)(&Data[I][J][K] - BaseAddr);
				//Write the address to the file
				fwrite(&ElementAddr, 4, 1, file1);
			}
		}
	}
	
	fclose(file1);

	sleep(1);

	printf("Starting Address Trace 2\n");
	// Create/open file
	FILE *file2 = fopen("AddressTraces2.txt", "wbt");

	for(K = 0; K < NbrCols; K++) {
		for(J = 0; J < NbrRows; J++) {
			for(I = 0; I < NbrPlanes; I++) {
				X = Data[I][J][K];
				ElementAddr = (int32_t*)(&Data[I][J][K] - BaseAddr);
				//Write the address to the file
				fwrite(&ElementAddr, 4, 1, file2);
			}
		}
	}

	fclose(file2);

	sleep(1);

	printf("Starting Address Trace 3\n");
	FILE *file3 = fopen("AddressTraces3.txt", "wbt");

	int tempPlanes[NbrPlanes];
	int tempRows[NbrRows];
	int tempCols[NbrCols];

	//Initialize integer arrays for shuffling
	for(I = 0; I < NbrPlanes; I++) {
		NbrPlanesArr[I] = I;
	}
	for(I = 0; I < NbrRows; I++) {
		NbrRowsArr[I] = I;
	}
	for(I = 0; I < NbrCols; I++) {
		NbrColsArr[I] = I;
	}

	// Randomly shuffle the arrays
	shuffleArray(NbrPlanesArr, NbrPlanes);
	shuffleArray(NbrRowsArr, NbrRows);
	shuffleArray(NbrColsArr, NbrCols);

	// Shuffles array based on the row, column, and plane indexing shuffled above.
	// Shuffles based on cols, and then rows, and finally planes
	for(I = 0; I < NbrPlanes; I++) {
		for(J = 0; J < NbrRows; J++) {
			for(K = 0; K < NbrCols; K++) {
				ElementAddr = (int32_t*)(&Data[NbrPlanesArr[I]][NbrRowsArr[J]][NbrColsArr[K]] - BaseAddr);
				fwrite(&ElementAddr, 4, 1, file3);
			}
		}
	}

	return(1);
}
