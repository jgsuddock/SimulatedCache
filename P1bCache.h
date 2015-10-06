 
#ifndef P1BCACHE_H
#define P1BCACHE_H

/* Max Line Length in Trace */
// #define LINELENGTH 128

/* Cache Sizes (in bytes) */
#define CACHE_SIZE 32768
#define BLOCK_SIZE 4 ///////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Block Sizes */
#define TAG 18 /* 18 + 0 = 18 */
#define INDEX 12 /* 18 + 12 = 30 */
#define OFFSET 2 /* 30 + 2 = 32 */


// Typedefs
typedef struct Cache_* Cache;
typedef struct Block_* Block;

Cache createCache(int cache_size, int block_size);
 
void destroyCache(Cache cache);

void read(Cache cache, char* address);

#endif
