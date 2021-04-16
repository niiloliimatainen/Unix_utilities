#include <stdio.h>
#include <stdlib.h>

void unzip(FILE *stream);

/*struct which has the "z" format (4 byte integer and 1 byte unsigned char)*/
typedef struct Zipchunk {
	int n;
	unsigned char c;
} Zipchunk;


int main(int argc, char **argv) {
     FILE *file;
    
    if (argc == 1) {
        printf("my-unzip: file1 [file2 ...]\n");
        exit(1);

    } else {
        for (int i = 1; i < argc; i++) {
        	if ((file = fopen(argv[i], "rb")) == NULL) {
        		fprintf(stderr, "Error: cannot open file '%s'\n", argv[i]);
      	        exit(1);
        	}
			unzip(file);
			fclose(file);
            printf("\n");
    	}
    }  
	return 0;  	
}


void unzip(FILE *stream){
	/*Integers which hold fread return values for loop condition*/
	int i_z, c_z;

	/*Function reads one number/character pair at a time, until it has nothing to read.*/

	while (1){

		/* Allocate memory in which we read from file*/
		Zipchunk *z = malloc(sizeof(Zipchunk));

		/*Check failed allocation*/
		if(z == NULL) {
			fprintf(stderr, "ERROR: could not allocate memory\n");
			exit (-1);
		}

		/*Read first the integer and then the character from file to zipchunk values*/
		i_z = fread(&z->n, sizeof(z->n), 1 , stream);
		c_z = fread(&z->c, sizeof(z->c), 1, stream);

		/* If we get both values, we continue, else we are done!*/
		if (i_z != 1 || c_z != 1) {
			free(z);
			break;
		}
		/*Write n amount of times letter c to the output stream*/
		for(int i =0; i < z->n; i++) {
			printf("%c",z->c);
		}
		free(z);
    } 
}