#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_DELAY 8000
#define DEFAULT_VOLUME 4
#define HEADER 22

// void addecho(int delay, int volume_scale, FILE *sourceFile, FILE *destFile);
  // -- not sure if this is needed or not -- 
//  

int main(int argc, char *argv[]) {

    int delay = DEFAULT_DELAY;
    int volume_scale = DEFAULT_VOLUME;
    

    // using getopt(): parses command line - returns -1 if no more options are present
    // ^ always runs in a loop
    // 
    while (int opt = getopt(argc, argv, "d:v:") != -1) {
          switch(opt) {
              case 'd': 
                  if (optarg < 0) {
                      fprintf(stderr, "Not positive integer");
                      // return 0? or exit(1)?------- 
                      }
  
                  else {
                    // converting ASCII to integer
                    delay = atoi(optarg)
                  }


              case 'v': 
                  if (optarg < 0) {
                      fprintf(stderr, "Not positive integer");
                      // return 0? or exit(1)?------- 
                      }
  
                  else {
                    // converting ASCII to integer
                    vol = atoi(optarg)
                  }

          }

              
              

  
