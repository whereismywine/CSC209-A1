#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h> 

#define DEFAULT_DELAY 8000
#define DEFAULT_VOLUME 4
#define HEADER_SIZE 22

// void addecho(int delay, int volume_scale, FILE *sourceFile, FILE *destFile);
  // -- not sure if this is needed or not -- 
//  

int main(int argc, char *argv[]) {
    int delay = DEFAULT_DELAY;
    float volume_scale = DEFAULT_VOLUME;
    int opt;

    // using getopt(): parses command line - returns -1 if no more options are present
    // ^ always runs in a loop

    // Parse command-line arguments
    while ((opt = getopt(argc, argv, "d:v:")) != -1) {
        switch (opt) {
            case 'd':
                delay = atoi(optarg);
                if (delay < 0) {
                    fprintf(stderr, "delay not positive integer");
                    return EXIT_FAILURE;
                }
                break;
            case 'v':
                volume_scale = atof(optarg);
                if (volume_scale <= 0) {
                    fprintf(stderr, "volume not positive integer");
                    return EXIT_FAILURE;
                }
                break;
            default:
                fprintf(stderr, "invalid command");
                return EXIT_FAILURE;
        }
    }

    // check if the command is valid
    if (argc - optind < 2) {
        fprintf(stderr, "Missing source or destination file arguments\n");
        return EXIT_FAILURE;
    }

    // open files
    FILE *srcFile = fopen(argv[optind], "rb");
    FILE *dstFile = fopen(argv[optind + 1], "wb");
    if (srcFile == NULL || dstFile == NULL) {
        perror("Failed to open files");
        return EXIT_FAILURE;
    }

    // writing the header 
    short header[HEADER_SIZE];
    if (fread(header, sizeof(short), HEADER_SIZE, srcFile) != HEADER_SIZE) {
        fprintf(stderr, "Error reading WAV header\n");
        fclose(srcFile);
        fclose(dstFile);
        return EXIT_FAILURE;
    }

    // adjust the size fields in the header
    unsigned int* fileSizeField = (unsigned int*)(header + 2); // byte 4, which is short index 2
    *fileSizeField += delay * 2;

    unsigned int* dataChunkSizeField = (unsigned int*)(header + 20); //byte 40, which is short index 20
    *dataChunkSizeField += delay * 2;

    // write header to dstFile
    if (fwrite(header, sizeof(short), HEADER_SIZE, dstFile) != HEADER_SIZE) {
        fprintf(stderr, "Failed to write adjusted WAV header\n");
        fclose(srcFile);
        fclose(dstFile);
        return EXIT_FAILURE;
    }

    // the echo buffer creation
    short *echoBuffer = (short *)malloc(delay * sizeof(short));
    if (echoBuffer == NULL) {
        perror("error with allocation for echo buffer");
        fclose(srcFile);
        fclose(dstFile);
        return EXIT_FAILURE;
    }
    memset(echoBuffer, 0, delay * sizeof(short));

    // the echo stuff here

    // end of program
    fclose(srcFile);
    fclose(dstFile);
    return EXIT_SUCCESS;
}
