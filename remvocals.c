#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    if (argc != 3){
        // add err msg
        return EXIT_FAILURE;
    }

    FILE *srcFile = fopen(argv[1], "rb");
    if (!srcFile) {
        // add error msg
        return EXIT_FAILURE;
    }

    FILE *dstFile = fopen(argv[2], "wb");
    if (!dstFile) {
        // add err msg
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

    fclose(srcFile);
    fclose(dstFile);

    return EXIT_SUCCESS;

}