#include <stdio.h>
#include <stdlib.h>

#define MAXLEN 1024

void read_file(FILE *stream);

/* This program takes file names as arguments and print out the contents of the files */
int main(int argc, char **argv) {
     FILE *file;
    
    if (argc == 1) {
        exit(0);
    
    } else {
        for (int i = 1; i < argc; i++) {

            if ((file = fopen(argv[i], "r")) == NULL) {
                printf("my-cat: cannot open file\n");
                exit(1);
            } 

            read_file(file);
            fclose(file);
        } 
    }
    return 0;
}

/* Helper function to print out all the lines in file */
void read_file(FILE *stream) {
    char line[MAXLEN];
    while (fgets(line, MAXLEN, stream) != NULL) {
        printf("%s", line);
    }
}

