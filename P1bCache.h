 
#ifndef SWIFT_SIM_H_
#define SWIFT_SIM_H_

/* Max Line Length in Trace */
#define LINELENGTH 128

/* Cache Sizes (in bytes) */
#define CACHE_SIZE 16384
#define BLOCK_SIZE 4 ///////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Block Sizes */
#define TAG 18 /* 18 + 0 = 18 */
#define INDEX 12 /* 18 + 12 = 30 */
#define OFFSET 2 /* 30 + 2 = 32 */


// Typedefs
typedef struct Cache_* Cache;
typedef struct Block_* Block;

Cache createCache(int cache_size, int block_size, int write_policy);
 
void destroyCache(Cache cache);

int read(Cache cache, char* address);

#endif
