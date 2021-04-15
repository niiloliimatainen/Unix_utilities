#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
     FILE *file;
    
    if (argc == 1) {
        printf("my-unzip: file1 [file2 ...]\n");
        exit(1);

    } else {
        for (int i = 1; i < argc; i++) {
            if ((file = fopen(argv[i], "r")) == NULL) {
      
            } 

      
        } 


    }
    return 0;
}