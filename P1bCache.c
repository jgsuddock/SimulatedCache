#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "P1bCache.h"

struct Block_ {
	char *tag;    
	int valid;
};

struct Cache_ {
    int hits;
    int misses;
    int cache_size;
    int block_size;
    int numLines;
    Block* blocks;    
};

unsigned int hexToDecimal (const char str[]) {

	unsigned int result = 0;
	int sub = 0;	

	for(int i = 4; i > 0; i--) {
		for(int j = 1; j > -1; j--) {
			sub = j;
			if(i < 3) {
				sub++;
			}
			result = result * 16;
			if(str[i*2 - sub] >= '0' && str[i*2 - sub] <= '9')
			{
				result = result + (str[i*2 - sub] - '0');
			}
			else if(str[i*2 - sub] >= 'a' && str[i*2 - sub] <= 'f')
			{
				result = result + (str[i*2 - sub] - 'a') + 10;
			}
		}
	}

	return result;

}

int binToDecimal (char *bin) {

	int lengthBin = strlen(bin);
	int decSum = 0;

	for(int i = 0; i < lengthBin; i++) {
		decSum = decSum * 2;		
		if(bin[i] == '1') {
			decSum++;
		}
	} 

	return decSum;

}

char *decToBinary(unsigned int num) {
	char* binStr[33];
	int bitState;
	    
	//binStr = (char*) malloc(sizeof(char) * 33);
	//assert(binStr != NULL); //Needed?
	    
	binStr[32] = '\0';
	    
	for(int i = 0; i < 32; i++ ) {
		bitState = num & (1 << i);
		if(bitState == 0) {
			binStr[31-i] = '0';
		} else {
			binStr[31-i] = '1';
		}
	}
	    
	return binStr;
}

char *getTag(char *binStr) {
	
	char *tag;
	tag = (char *) malloc(sizeof(char) * 18);
	
	tag[17] = '\0';
	
	for(int i = 0; i < 17; i++)
	{
		tag[i] = binStr[i];
	}
	
	return tag;

}

char *getIndex(char *binStr) {
	
	char *index;
	index = (char *) malloc(sizeof(char) * 10);
	
	index[9] = '\0';
	
	for(int i = 0; i < 9; i++)
	{
		index[i] = binStr[i+17];
	}
	
	return index;

}

char *getData(char *binStr) {
	
	char *data;
	data = (char *) malloc(sizeof(char) * 7);
	
	data[6] = '\0';
	
	for(int i = 0; i < 6; i++)
	{
		data[i] = binStr[i+26];
	}
	
	return data;

}

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
	if(cache->blocks != NULL) {
		fputs ("Blocks Memory Allocation Error: ", stderr);
		return 0;
	}
	cache->blocks[i]->valid = 0;

	for(I = 0; I < cache->numLines; i++) {
		cache->blocks[i] = (Block) malloc( sizeof( struct Block_ ) );
		if(cache->blocks[i] != NULL) {
			fputs ("Blocks Memory Allocation Error: ", stderr);
			return 0;
		}
		cache->blocks[i]->valid = 0;
		cache->blocks[i]->tag = NULL;
	}

	return cache;
}

void read(Cache cache, char* address) {
	
	unsigned int dec = hexToDecimal(address);
	char *addr = decToBinary(dec);
	char *tag = getTag(addr);
	char *index = getIndex(addr);
	char *data = getData(addr);

	Block block = cache->blocks[index];
	if(block->valid == 1 && strcmp(block->tag, tag) == 0) {
		cache->hits++;
    		free(tag);
	} else {
		cache->misses++;
		
		if(block->tag != NULL) {
			free(block->tag);
		}
		block->tag = tag;
		block->valid = 1;
	}		
	
	free(addr);
	free(index);
	free(data);

}

void destroyCache(Cache cache) {
	
	if(cache != NULL) {
		for(int i = 0; i < cache->numLines; i++) {
			if(cache->blocks[i]->tag != NULL) {
				free(cache->blocks[i]->tag);
			}
	      		free(cache->blocks[i]);
		}
		free(cache->blocks);
		free(cache);
	}

	return;

}
