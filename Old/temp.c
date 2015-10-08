#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

struct bin
	{
		void* x;
	};


int main(int argc, char const *argv[])
{

	FILE* file;
	int i = 0;
	int numAddr = 67102721; 

	struct bin buffer;

	file = fopen( "AddressTraces/AddressTraces1.txt", "rb" );

	while(fread(&buffer, sizeof(struct bin), 1, file) && i < numAddr) {
		    if(i == numAddr - 2) {
		    	printf("%i %p\n", i, buffer.x);
		    }
		    
		    i++;
    }

    int32_t j = (int32_t)buffer.x;
    printf("%i %p\n", i, buffer.x);

    fclose(file);

	return 0;
}

//int i = 0;
//ifs.read((char*) (&i), sizeof(i));