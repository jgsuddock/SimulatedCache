#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{

	if(argc < 2) {
		printf("Missing Arguments (./Program traceFilename.txt)");
		return 0;
	}

	//Using Read Instructions from http://www.cplusplus.com/reference/cstdio/fread/
	FILE * tracefile;
	long lSize;
	char * tracebuffer;
	size_t result;

	pFile = fopen ( argv[1] , "rb" );
	if (pFile == NULL) {
		fputs ("Open File Error: ",stderr);
		return 0;
	}

	fseek (tracefile , 0 , SEEK_END); //Pull file size
	lSize = ftell (tracefile);
	rewind (tracefile);

	//Allocate Memory for File
	tracebuffer = (char*) malloc (sizeof(char)*lSize);
	if (tracebuffer == NULL) {
		fputs ("Memory Allocation Error: ", stderr);
		return 0;
	}

	// File put in buffer:
	result = fread (tracebuffer, 1, lSize, pFile);
	if (result != lSize) {
		fputs ("File Read Error: ", stderr);
		return 0;
	}

	// terminate
	fclose (tracefile);
	free (tracebuffer);

	printf("Cache:\n\tCACHE HITS: %i\n\tCACHE MISSES: %i\n\tCACHE SIZE: %i Bytes\n\tBLOCK SIZE: %i Bytes\n\tNUM LINES: %i\n", cache->hits, cache->misses, cache->cache_size, cache->block_size, cache->numLines);

	return 0;
}

Cache createCache(int cacheSize, int blockSize) {
	Cache cache;
	int I;

	cache = (Cache) malloc( sizeof( struct Cache_ ) );
	if (cache == NULL) {
		fputs ("Cache Memory Allocation Error: ", stderr);
		return 0;
	}

	cache->hits = 0;
	cache->misses = 0;
	cache->cacheSize = cacheSize;
	cache->blockSize = blockSize;

	cache->numLines = (int)(cacheSize / blockSize);

	cache->blocks = (Block*) malloc( sizeof(Block) * cache->numLines );

	for(I = 0; I < cache->numLines; i++) {
		cache->blocks[i] = (Block) malloc( sizeof( struct Block_ ) );
		if(cache->blocks[i] != NULL) {
			
		}
		cache->blocks[i]->valid = 0;
		cache->blocks[i]->tag = NULL;
	}

	return cache;
}