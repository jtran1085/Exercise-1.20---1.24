/*
 * Exercise 1-23
 * Write a program to remove all comments from a C program.
 * Don't forget to handle quoted strings and character constants properly.
 * C comments don't nest.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "files.h"
#include <stdarg.h>
#include <stdbool.h>

#define MAXLINE 5000

bool open_io_files(int argc, const char* argv[], FILE** fin, FILE** fout,
                   int min_expected_argc, int max_expected_argc,
                   const char* usage) {
  /* open an input file, and optionally an output file */
  if (argc < min_expected_argc || argc > max_expected_argc) {
    fprintf(stderr, "%s\n", usage);
    return false;
  }

  *fin = fopen(argv[1], "r");
  if (*fin == NULL) {
    fprintf(stderr, "failed to open input file: '%s'\n", argv[1]);
    return false;
  }
            // In this case, we don't want to open output file
  if (fout == NULL) {  return true; }  // everything cool

  *fout = fopen(argv[2], "w");
  if (*fout == NULL) {  // output file failed to open
    fprintf(stderr, "failed to open output file: '%s'\n", argv[2]);
    fprintf(stderr, "closing already open input file: '%s'\n", argv[1]);
    fclose(*fin);
    return false;
  }

  return true;
}

    // must include <stdarg.h>  -- see files.h
void closefiles(int n, ...) {   // uses varargs (variable # of args)
  va_list pargs;
  va_start (pargs, n);    // initialize the list ptr

  for (int i = 0; i < n; i++)
    fclose(va_arg (pargs, FILE*));  // get next argument

  va_end (pargs);   // clean up
}


int getTheLine(char line[], int limit);

int main(int argc, const char * argv[]) {

  if(argc!=2){
    fprintf(stderr, "Usage: ./comments inputfile");
    exit(1);
  }


  int size = 0;
  char c;
  int i = 0;
  int j =0;
  FILE* fin;
  FILE* fout = fopen("output.c", "w");
  bool isCom = false;

  char commentArray[MAXLINE+1];
  char newArray[MAXLINE+1];
  memset(commentArray,' ',sizeof(commentArray));
  memset(newArray,' ',sizeof(newArray));

  while((c=fgetc(fin))!=EOF && c!= '\0'){
    commentArray[size] = c;
    size++;
  }
  commentArray[size] = '\0';

  for( i =0, j=0; i<size; i++){
      if(commentArray[i] =='/' && commentArray[i+1] == '*'){
        printf("IN\n");
        isCom = true;
      }
      if(isCom && commentArray[i] == '*' && commentArray[i+1] == '/'){
        printf("OUT\n");
        i++;
        isCom = false;
      }
      if(commentArray[i]=='/' && commentArray[i+1] == '/'){
        printf("IN\n");
        isCom = true;
      }
      if(isCom && commentArray[i] == '\n'){
        printf("OUT\n");
        isCom = false;
      }
      if(!isCom){
        newArray[j++]=commentArray[i];
      }
      size = j;
    }
  newArray[size]='\0';
  fprintf(fout, "%s",newArray);
  closefiles(2, fin, fout);
  return 0;
}
