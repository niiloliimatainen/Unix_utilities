#include <stdio.h>
#include <stdlib.h>

void unzip(FILE *stream);

int main(int argc, char **argv) {
     FILE *file;
    
    if (argc == 1) {
        printf("my-unzip: file1 [file2 ...]\n");
        exit(1);

    /*} else {
        for (int i = 1; i < argc; i++) {
            if ((file = fopen(argv[i], "r")) == NULL) {
                exit(1);
            } 
            un_zip();

      
        } 
    */
    }else{
        file = fopen("test.txt", "r");
        unzip(file);
    }
return 0;  
    
   
}

void unzip(FILE *stream){
    char *buffer = NULL;
    size_t bufsize= 5;
    int x;
    
    while ( x =fread(&buffer, bufsize, 1, stream) > 0){
        printf("%c\n", buffer);
    }
}