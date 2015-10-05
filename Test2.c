#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

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

//assert(formatted != NULL);
    
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

// Dont't really need this (only read)
int write(Cache cache, char* address) {
	
	unsigned int dec = hexToDecimal(address);
	char *addr = decToBinary(dec);
	char *tag = getTag(addr);
	char *index = getIndex(addr);
	char *data = getData(addr);

	Block block = cache->blocks[index];
	if(block->valid == 1 && strcmp(block->tag, tag) == 0) {
		cache->hits++;
		//dirty, free tag
	} else {
		cache->misses++;
		//cache->reads++;
		//cache->writes++;
		//dirty
		
		if(block->tag != NULL) {
			free(block->tag);
		}
		block->tag = tag;
		block->valid = 1;
	}		
	
	//free(addr);
	//free(index);
	//free(data);

	return 1; //successful

}

// Don't really need this.
void printCache(Cache cache) {
	
	printf("Cache:\n\tCACHE HITS: %i\n\tCACHE MISSES: %i\n\tCACHE SIZE: %i Bytes\n\tBLOCK SIZE: %i Bytes\n\tNUM LINES: %i\n", cache->hits, cache->misses, cache->cache_size, cache->block_size, cache->numLines);

}
