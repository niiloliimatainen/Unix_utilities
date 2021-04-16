#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void my_zip(FILE *stream);
void write_stdout(int count, int tmp);


/* This programs take one or many files in and compress them into a single zip file */
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
    return 0;
}


/* Helper function to write the compressed content to the standard output */ 
void write_stdout(int count, int tmp) {
    char ch = tmp;
    /* If count is 0, char is a newline */
    if (count != 0) {
        printf("%d", count);
        /*fwrite(&count, 4, 1, stdout);*/
    } 
    printf("%c", ch);
    /*fwrite(&ch, 1, 1, stdout);*/
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
        
        
        /* Counting sequential occurrences of chars */
        if (ch == tmp) {
            count++;
        
        /* If char is a newline, write that to compressed file */
        } else if (ch == '\n') {
            write_stdout(count, tmp);
            tmp = ch;
            count = 0;

        /* When char changes, send the results to write_stdout() */
        } else {
            write_stdout(count, tmp);
            tmp = ch;
            count = 1;
        }
    }
    /* Writing a newline to the end of the compressed content of the file */
    write_stdout(0, '\n');
}

