#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define DEFAULT_DELAY 8000
#define DEFAULT_VOLUME_SCALE 4.0
#define HEADER_SIZE 44 

int main(int argc, char *argv[]) {
    int delay = DEFAULT_DELAY;
    float volume_scale = DEFAULT_VOLUME_SCALE;
    int opt;

    // parse the command-line arguments
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
        fprintf(stderr, "Missing source or destination WAV file.\n");
        exit(EXIT_FAILURE);
    }
    // open files
    FILE *srcFile = fopen(argv[optind], "rb");
    FILE *destFile = fopen(argv[optind + 1], "wb");
    if (!srcFile || !destFile) {
        perror("Failed to open files");
        exit(EXIT_FAILURE);
    }

    // read and adjust WAV header
    unsigned char header[HEADER_SIZE];
    if (fread(header, 1, HEADER_SIZE, srcFile) != HEADER_SIZE) {
        fprintf(stderr, "Error reading WAV header\n");
        fclose(srcFile);
        fclose(destFile);
        exit(EXIT_FAILURE);
    }

    unsigned int *fileSizeField = (unsigned int *)(header + 4); 
    unsigned int *dataChunkSizeField = (unsigned int *)(header + 40); 

    // adjust file size for echo
    *fileSizeField += delay * 2; 
    *dataChunkSizeField += delay * 2;
    fwrite(header, 1, HEADER_SIZE, destFile);

    // prepare echo buffer
    short *echoBuffer = (short *)malloc(delay * sizeof(short));
    if (echoBuffer == NULL) {
        perror("error with allocation for echo buffer");
        fclose(srcFile);
        fclose(destFile);
        exit(EXIT_FAILURE);
    }
    memset(echoBuffer, 0, delay * sizeof(short));

    size_t samplesRead, samplesWritten;
    short sample, echoSample;
    int bufferIndex = 0;

    // mixing original and echo samples
    while ((samplesRead = fread(&sample, sizeof(short), 1, srcFile)) == 1) {
        echoSample = echoBuffer[bufferIndex];
        short mixedSample = sample + (short)(echoSample / volume_scale);
        echoBuffer[bufferIndex] = sample;
        bufferIndex = (bufferIndex + 1) % delay;
        samplesWritten = fwrite(&mixedSample, sizeof(short), 1, destFile);
        if (samplesWritten != 1) {
            perror("Failed to write sample");
            free(echoBuffer);
            fclose(srcFile);
            fclose(destFile);
            exit(EXIT_FAILURE);
        }
    }

    // write remaining echo
    for (int i = 0; i < delay; ++i) {
        echoSample = echoBuffer[(bufferIndex + i) % delay] / volume_scale;
        fwrite(&echoSample, sizeof(short), 1, destFile);
    }

    
    // end of program
    free(echoBuffer);
    fclose(srcFile);
    fclose(destFile);
    return 0;
}
