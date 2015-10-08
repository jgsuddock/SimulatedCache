 
#ifndef P1BCACHE_H
#define P1BCACHE_H

// Cache Sizes (in bytes)
#define CACHE_SIZE 32768
#define BLOCK_SIZE 4
#define LINE_SIZE 8192 

// Block Sizes
#define TAG 17
#define INDEX 9
#define OFFSET 6


// Typedefs
typedef struct Cache_* Cache;
typedef struct Block_* Block;

Cache createCache(int cacheSize, int blockSize);
 
void destroyCache(Cache cache);

void read(Cache cache, int dec);

#endif
