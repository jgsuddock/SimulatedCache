#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "P1bCache.h"

struct Block_ {
	char* tag;    
	int valid;
};

struct Cache_ {
    int hits;
    int misses;
    int cacheSize;
    int blockSize;
    int numLines;
    Block* blocks;    
};

struct bin
{
	int32_t* x;
};

int binToDecimal (char *bin) {

	int lengthBin = strlen(bin);
	int decSum = 0;
	int i;

	for(i = 0; i < lengthBin; i++) {
		decSum = decSum * 2;		
		if(bin[i] == '1') {
			decSum++;
		}
	} 

	return decSum;

}

char *decToBinary(unsigned int num) {
	char* binStr;
	int bitState;
	int i;
	    
	binStr = (char*) malloc(sizeof(char) * 33);
	
	binStr[32] = '\0';
	    
	for(i = 0; i < 32; i++ ) {
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
	
	int i;
	char *tag;
	tag = (char *) malloc(sizeof(char) * 18);
	
	tag[17] = '\0';
	
	for(i = 0; i < 17; i++)
	{
		tag[i] = binStr[i];
	}
	
	return tag;

}

char *getIndex(char *binStr) {
	
	int i;
	char *index;
	index = (char *) malloc(sizeof(char) * 10);
	
	index[9] = '\0';
	
	for(i = 0; i < 9; i++)
	{
		index[i] = binStr[i+17];
	}
	
	return index;

}

char *getData(char *binStr) {
	
	int i;
	char *data;
	data = (char *) malloc(sizeof(char) * 7);
	
	data[6] = '\0';
	
	for(i = 0; i < 6; i++)
	{
		data[i] = binStr[i+26];
	}
	
	return data;

}

int main(int argc, char const *argv[]) {
    Cache cache;
    FILE *file;
	int i = 0;
	struct bin buffer;
   
    file = fopen( argv[1], "r" );

    cache = createCache(CACHE_SIZE, BLOCK_SIZE);

    while(fread(&buffer, sizeof(struct bin), 1, file)) {
		read(cache, *buffer.x);
    }

  	printf("CACHE HITS: %i\nCACHE MISSES: %i\n", cache->hits, cache->misses);
  
    fclose(file);
    destroyCache(cache);
    cache = NULL;
    
    return 1;

}

Cache createCache(int cacheSize, int blockSize) {
	Cache cache;
	int i;

	cache = (Cache) malloc( sizeof( struct Cache_ ) );
	if (cache == NULL) {
		fputs ("Cache Memory Allocation Error: ", stderr);
		return 0;
	}

	cache->hits = 0;
	cache->misses = 0;
	cache->cacheSize = CACHE_SIZE;
	cache->blockSize = BLOCK_SIZE;
	cache->numLines = (int)(CACHE_SIZE / BLOCK_SIZE);

	cache->blocks = (Block*) malloc( sizeof(Block) * cache->numLines );
	if(cache->blocks == NULL) {
		fputs ("Blocks X Memory Allocation Error: ", stderr);
		return 0;
	}

	for(i = 0; i < cache->numLines; i++) {
		cache->blocks[i] = (Block) malloc( sizeof( struct Block_ ) );
		if(cache->blocks[i] == NULL) {
			fputs ("Blocks Y Memory Allocation Error: ", stderr);
			return 0;
		}
		cache->blocks[i]->valid = 0;
		cache->blocks[i]->tag = NULL;
	}

	return cache;
}

void read(Cache cache, int dec) {
	
	char *addr = decToBinary(dec);
	char *tag = getTag(addr);
	char *index = getIndex(addr);
	char *data = getData(addr);
	int indexDec = binToDecimal(index);

	Block block = cache->blocks[indexDec];
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
	
	int i;

	if(cache != NULL) {
		for(i = 0; i < cache->numLines; i++) {
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
