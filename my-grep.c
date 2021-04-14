#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLEN 1024
void my_grep(FILE *stream, char* pattern);

int main(int argc, char *argv[]){
    FILE *input_f;

    /*Validate input arguments*/
    if (argc == 2){
        my_grep(stdin, argv[1]);
        /* read from stdin*/

    } else if (argc > 2){
        /*loop throug all input files so: argv[3], 4, 5 and so forth*/
        /*Try open*/

        for (int f_nbr = 2; f_nbr < argc; f_nbr++){
            
            if ((input_f = fopen(argv[f_nbr], "r")) == NULL) {
			    fprintf(stderr, "Error: cannot open file '%s'\n", argv[f_nbr]);
			    exit(1);
		    }
            my_grep(input_f, argv[1]);
            
        }

    } else{
        /*print how to use */
        exit(1);
    }


}

void my_grep(FILE *stream, char* pattern){
    char *buffer;
    size_t bufsize = MAXLEN;
    ssize_t length;
    while (1){
        buffer = (char*)malloc(bufsize * sizeof(char));
        if( buffer == NULL){
            perror("Unable to allocate buffer");
            exit(1);
        }
        length = getline(&buffer, &bufsize, stream);
        if (length < (ssize_t)0 && strcmp(buffer, "-1\n")){
            break;
        }
        if (length > (ssize_t)0 && buffer[length - 1] == '\n'){
            buffer[--length] = '\0';
        }
        
        printf("%s\n",buffer);

        
    }
}

