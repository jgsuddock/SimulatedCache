#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "P1bCache.h"

//Defined data types used in cache allocation
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

/*
 * Inputs binary number (as a char array)
 * Returns decimal form of the number (as an integer)
 */
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

/*
 * Inputs decimal number
 * Returns binary form of number (as a char array)
 */
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

/*
 * Inputs the binary address (as a char array)
 * Returns tag bits of address
 */
char *getTag(char *binStr) {
	
	int i;
	char *tag;
	// Allocates variable holder to hold tag value.
	tag = (char *) malloc(sizeof(char) * 18);
	
	tag[17] = '\0'; // End of array
	
	for(i = 0; i < 17; i++)
	{
		tag[i] = binStr[i];
	}
	
	return tag;

}

/*
 * Inputs the binary address (as a char array)
 * Returns line index bits of address
 */
char *getIndex(char *binStr) {
	
	int i;
	char *index;
	// Allocates variable holder to hold index value.
	index = (char *) malloc(sizeof(char) * 10);
	
	index[9] = '\0';
	
	for(i = 0; i < 9; i++)
	{
		index[i] = binStr[i+17];
	}
	
	return index;

}

/*
 * Inputs the binary address (as a char array)
 * Returns data bits of address
 */
char *getData(char *binStr) {
	
	int i;
	char *data;
	// Alocates variable holder to hold data value
	data = (char *) malloc(sizeof(char) * 7);
	
	data[6] = '\0';
	
	for(i = 0; i < 6; i++)
	{
		data[i] = binStr[i+26];
	}
	
	return data;

}

/*
 * Main:
 * 
 * Reads file and defines cache constructor
 */

int main(int argc, char const *argv[]) {
    Cache cache;
    FILE *file;
	int i = 0;
	struct bin buffer;
   
	//Starts file stream with address trace
    file = fopen( argv[1], "r" );

    //Defines cache constructor
    cache = create(CACHE_SIZE, BLOCK_SIZE);

    //Reads each line of the file into the buffer structure
    while(fread(&buffer, sizeof(struct bin), 1, file)) {
		read(cache, *buffer.x);
    }

  	printf("CACHE HITS: %i\nCACHE MISSES: %i\n", cache->hits, cache->misses);
  
  	//Calls Destructors
    fclose(file);
    destroyCache(cache);
    cache = NULL;
    
    return 1;

}

/*
 * Cache constructor allocating blocks within.
 */
Cache create(int cacheSize, int blockSize) {
	Cache cache;
	int i;

	//Allocating memory for cache
	cache = (Cache) malloc( sizeof( struct Cache_ ) );
	if (cache == NULL) {
		fputs ("Cache Memory Allocation Error: ", stderr);
		return 0;
	}

	//Initializing Cache Variables
	cache->hits = 0;
	cache->misses = 0;
	cache->cacheSize = CACHE_SIZE; //Defined in header
	cache->blockSize = BLOCK_SIZE;
	cache->numLines = (int)(CACHE_SIZE / BLOCK_SIZE);

	//Allocates memory for the cache blocks.
	cache->blocks = (Block*) malloc( sizeof(Block) * cache->numLines );
	if(cache->blocks == NULL) {
		fputs ("Blocks Memory Allocation Error: ", stderr);
		return 0;
	}

	//Allocates memory for each cache block defined previously (numLines allocations)
	for(i = 0; i < cache->numLines; i++) {
		cache->blocks[i] = (Block) malloc( sizeof( struct Block_ ) );
		if(cache->blocks[i] == NULL) {
			printf("Block %i Memory Allocation Error\n", i);
			fputs ("Error: ", stderr);
			return 0;
		}
		//Initialize block variables
		cache->blocks[i]->valid = 0;
		cache->blocks[i]->tag = NULL;
	}

	return cache;
}

/*
 * Read method to read the address passed and simulate cache behavior.
 */
void read(Cache cache, int dec) {
	
	// Get the needed information from the passed address.
	char *addr = decToBinary(dec);
	char *tag = getTag(addr);
	char *index = getIndex(addr);
	char *data = getData(addr);
	int indexDec = binToDecimal(index);

	// Get the block with that line index number.
	Block block = cache->blocks[indexDec];
	// Compare the tag and check if it is valid.
	// If both are true, then it's a hit.
	// If not, then it's a miss.
	if(block->valid == 1 && strcmp(block->tag, tag) == 0) {
		cache->hits++;
    		free(tag);
	} else {
		cache->misses++;
		
		// Replace the tag of this block with the new tag.
		if(block->tag != NULL) {
			free(block->tag);
		}
		block->tag = tag;
		block->valid = 1; // Make the block valid after reading it in.
	}		
	
	free(addr);
	free(index);
	free(data);

}

/*
 * Destructor for Cache constructor
 * 
 * Removes each row of blocks and finally removes the cache.
 */
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
