#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void my_zip(FILE *stream);
void write_stdout(int count, int tmp);


/* This programs takes one or many files in and compress them to a single zip file */
int main(int argc, char *argv[]) {
     FILE *file;
    
    if (argc == 1) {
        printf("my-zip: file1 [file2 ...]\n");
        exit(1);
    
    } else {

        for (int i = 1; i < argc; i++) {
            if ((file = fopen(argv[i], "r")) == NULL) {
                fprintf(stderr, "Error: cannot open file '%s'\n", argv[i]);
			    exit(1);
            } 

            my_zip(file);
            fclose(file);
        } 


    }
    printf("\n");
    return 0;
}


/* Helper function to write the compressed content to the standard output */ 
void write_stdout(int count, int tmp) {
    char ch = tmp;
    fwrite(&count, 4, 1, stdout);
    fwrite(&ch, 1, 1, stdout);
}


/* Function that compress file's contents with run-length encoding (RLE) */
void my_zip(FILE *stream) {
    int ch;
    int tmp;
    int count = 1;

    /* Reading first char in file */
    tmp = fgetc(stream);

    /* Reading the file char by char */ 
    while ((ch = fgetc(stream)) != EOF) {
        /* Counting sequential occurences of chars */
        if (ch == tmp) {
            count++;
        
        /* When char changes, send the results to write_stdout() */
        } else {
            write_stdout(count, tmp);
            tmp = ch;
            count = 1;
        }
    }
    /* Sending last char's results to write_stdout() */
    write_stdout(count, tmp);
}

