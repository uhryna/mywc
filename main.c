#include <stdlib.h>
#include <string.h>
#include <stdio.h>
enum Array{CHARS, WORDS, LINES};

int* reading(FILE* fp, int* array){
  char primary;
  int wc = 0, lines = 0, chars = 0, in_word = 0;

  while((primary = fgetc(fp)) != EOF){
    if(primary == ' ' || primary == '\n' || primary == '\t'){
      in_word = 0;
    }else{
      if(!in_word){
        wc++;
        in_word = 1;
      }
    }
    if(primary == '\n') lines++;
    chars++;
  }
  array[CHARS] = chars;
  array[WORDS]= wc;
  array[LINES] = lines;
  return array;
}

#define FLAG_W (char)1
#define FLAG_C (char)2
#define FLAG_L (char)4

int main(int argc, char **argv){
  char flags;
  FILE* fp;
  if(argc >= 3){
    for(int i = 1; i<argc; i++){
      if(strcmp(argv[i], "-l") == 0)flags |= FLAG_L;
      if(strcmp(argv[i], "-w") == 0)flags |= FLAG_W;
      if(strcmp(argv[i], "-c") == 0)flags |= FLAG_C;
    }
    fp = fopen(argv[argc-1], "r");
  }else if(argc == 2 && argv[1] != "-l" && argv[1] != "-w" && argv[1] != "-c"){
    flags = 7;
    fp = fopen(argv[1], "r");
  }else{
    fprintf(stderr, "The file name is missing");
  }
  
  if(fp == NULL){
    fprintf(stderr, "Error: file didn't open");
    return 1;
  }
  int* array = malloc(sizeof(int)*3);
  array = reading(fp, array);
  if(flags & FLAG_W) printf("Words: %d\n", array[WORDS]);
  if(flags & FLAG_C) printf("Chars: %d\n", array[CHARS]);
  if(flags & FLAG_L) printf("Lines: %d\n", array[LINES]);
  free(array);
  return 0;
}
