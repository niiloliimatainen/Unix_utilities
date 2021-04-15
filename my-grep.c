#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLEN 1024

void my_grep(FILE *stream, char* pattern);

int main(int argc, char *argv[]){
    FILE *input_f;

    if (argc == 2){
        printf("Stop typing with <ctrl + Z or D>\n");
        /* read from stdin*/
        my_grep(stdin, argv[1]);
        return 0;
        

    } else if (argc > 2){
        /*loop throug all input files so: argv[3], [4], [5] and so forth*/
        /*Try open, if ok -> go grep*/

        for (int f_nbr = 2; f_nbr < argc; f_nbr++){
            
            if ((input_f = fopen(argv[f_nbr], "r")) == NULL) {
			    fprintf(stderr, "Error: cannot open file '%s'\n", argv[f_nbr]);
			    exit(1);
		    }
            my_grep(input_f, argv[1]);
            fclose(input_f);
            
        }
        return 0;

    } else{
        /*if no arguments are given, print instructions*/
        printf("my-grep: searchterm [file] [additional file]...\n");
        exit(1);
    }
}

void my_grep(FILE *stream, char* pattern){
    char *buffer;
    size_t bufsize = MAXLEN;
    ssize_t length;
    char *match;

    while (1){

        /*Allocate "unlimited" buffer of memory for getline*/

        buffer = (char*)malloc(bufsize * sizeof(char));
        if( buffer == NULL){
            perror("Unable to allocate buffer");
            exit(1);
        }

        length = getline(&buffer, &bufsize, stream);

        /*If we reach EOF ->free(buffer)->break*/
        if (length == -1){
            free(buffer);
            /*EOF stops loop*/
            break;
        }
        /*from: https://cboard.cprogramming.com/c-programming/168265-grep-program.html, if statement to remove excess newlines */   
        if (length > (ssize_t)0 && buffer[length - 1] == '\n'){
            buffer[--length] = '\0';
            
        }
        /*strstr function takes buffer and checks for given pattern*/
        match = strstr(buffer, pattern);

        /*if match pointer != null ->print line*/
        if (match != NULL){
            printf("%s\n", buffer);
        }
        /*Free after each line*/
        free(buffer);
    }
}

