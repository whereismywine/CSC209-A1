#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    if (argc != 3){
        // add err msg
        perror("Not enough arguments for program to run!");
        return EXIT_FAILURE;
    }

    FILE *srcFile = fopen(argv[1], "rb");
    if (srcFile == NULL) {
        // add error msg
        perror("Had trouble opening the file");
        return EXIT_FAILURE;
    }

    FILE *dstFile = fopen(argv[2], "wb");
    if (dstFile == NULL) {
        // add err msg
        perror("Had trouble creating a destination file");
        fclose(dstFile); 
        return EXIT_FAILURE;
    }  

    // THE ALGORITHM

    // write the first 44 bytes from input file to output file
    for (int i = 0; i < 44; i++) {
        unsigned char byte;
        // read and write one byte
        fread(&byte, 1, 1, srcFile); 
        fwrite(&byte, 1, 1, dstFile); 
    }

    //TODO: add error handling for if the file isnt 44 bytes, other errors

    // the seqwuence of shorts, and the math
    short left, right, combined;

    while (fread(&left, sizeof(short), 1, srcFile) == 1 &&
           fread(&right, sizeof(short), 1, srcFile) == 1) {
        combined = (left - right) / 2;

        // write two copies of the combined to output file
        fwrite(&combined, sizeof(short), 1, dstFile);
        fwrite(&combined, sizeof(short), 1, dstFile);
    }

    printf("Vocals removed successfully");

    fclose(srcFile);
    fclose(dstFile);

    return EXIT_SUCCESS; 

}
