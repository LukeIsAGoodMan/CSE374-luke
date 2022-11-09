/* Copyright 2022 PEIYAO HE luke
   CSE374 HW3
*/ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
/* 11.7 3:42
   HE PEIYAO */ 


// countw function do the wc of each file
void countw(FILE *file, int* d, int* e, int* f) {
  /* a b c corresponding to the char line words
     of this file, after computed, pass this value
     to the pointer d e f, use d e f in main */
  int a=0;
  int b=0;
  int c=0;
  int is=1;
  int ch, last='\n';
  while ((ch = fgetc(file))!=EOF) {
    last = ch;
    a++;
    if (isspace(ch)) {
      is = 1;
      if (ch == '\n') {
        b++;
      }
    } else {
      c += is;
      is = 0;
    }
  }
  if (last != '\n') {
    b++;
  }
  *d = a;
  *e = b;
  *f = c;
}


int main(int argc, char *argv[argc+1]) {
  // divide into two situation with option or not.
  if (argc <2) {
      printf("Usage:./wordcount requires an input file.\n");
      return EXIT_FAILURE;
    }
  if (strcmp(argv[1], "-l")==0||
      strcmp(argv[1], "-w")==0||
      strcmp(argv[1], "-c")==0) {
    // with option.
    // deal with th no input file situatiob first.
    if (argc<3) {
      printf("Usage:./wordcount requires an input file.\n");
      return EXIT_FAILURE;
    }
    // try open every file and read them.
    for (int i=2; i<argc; i++) {
      FILE *file = fopen(argv[i], "r");
      if (!file) {
        fprintf(stderr, "%s will not open. Skipping.\n", argv[i]);
      } else {
        int tot_chars;
        int tot_lines;
        int tot_words;
        countw(file, &tot_chars, &tot_lines, &tot_words);
        if (strcmp(argv[1], "-l")==0) {
          printf("%d\n", tot_lines);
        }
        if (strcmp(argv[1], "-w")==0) {
          printf("%d\n", tot_words);
        }
        if (strcmp(argv[1], "-c")==0) {
          printf("%d\n", tot_chars);
        }
        fclose(file);
      }
    }
  } else {
    // without option
    // try open every arguments as file and read them
    int total=0;
    for (int i=1; i<argc; i++) {
      FILE *file = fopen(argv[i], "r");
      if (!file) {
        fprintf(stderr, "%s will not open. Skipping.\n", argv[i]);
      } else {
        int tot_chars;
        int tot_lines;
        int tot_words;
        countw(file, &tot_chars, &tot_lines, &tot_words);
        total=total+tot_lines;
        printf("%d %d %d %s\n", tot_lines, tot_words, tot_chars, argv[i]);
      }
    }
    printf("Total Lines = %d\n", total);
  }
  return EXIT_SUCCESS;
}
