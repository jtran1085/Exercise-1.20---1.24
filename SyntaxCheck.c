#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "files.h"
#include <stdarg.h>
#include <stdbool.h>

#define MAXLINE 1000

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

int main(int argc, const char* argv[]){
  char line[MAXLINE];
  FILE* fin;
  FILE* fout;
  int len=0; 
  int t = 0;
  int brace=0;
  int brack=0;
  int paren = 0; 
  int sQuo = 1; 
  int dQuo = 1;

  while ((len = getTheLine(line,MAXLINE)) >0){
    t = 0;
    while (t++ < len){
      if(line[t] == '[') {brace++;}
      if(line[t] == ']') {brace--;}
      if(line[t] == '(') {paren++;}
      if(line[t] == ')') {paren--;}
      if(line[t] == '\'') {sQuo*=-1;}
      if(line[t] == '"') {dQuo*=-1;}
      if(line[t] == '{') {brack++;}
      if(line[t] == '}') {brack--;}
    }
  }
  if(brace!=0) { printf("Braces are not matching!\n");}
  if(brack!=0) { printf("Brackets are not matching!\n");}
  if(paren!=0) { printf("Parenthesis are not matching!\n");}
  if(sQuo!=1) { printf("Single Quotation Marks are not matching!\n");}
  if(dQuo!=1) { printf("Double Quotation Marks braces are not matching!\n");}
  else {
    printf("Syntax is correct.\n");
  }
}

int getTheLine(char line[], int limit)
{
  int c, i;
  
  for ( i=0;i<limit-1 && (c=getchar()) != EOF && c != '\n'; ++i)
    line[i] = c;
  if(c == '\n') 
    {
      line[i] = c;
      ++i;
    }
  line[i] = '\0';
  return i;

}
