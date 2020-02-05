//
//  main.c
//  detab
//
//  Created by William McCarthy on 032//20.
//  Copyright © 2020 William McCarthy. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "files.h"

#define TAB_INTERVAL 10
#define MAX_TAB_INTERVAL 80

int main(int argc, const char * argv[]) {
  FILE* fin;
  FILE* fout;

        // set tab_interval or use default
  int tab_interval = argc == 4 ? atoi(argv[3]) : TAB_INTERVAL;
  if (tab_interval > 80) {
    fprintf(stderr, "tabstops must be <= 80 characters\n");
    exit(2);
  }

  
        // open input and output files
  if (!open_io_files(argc, argv, &fin, &fout, 3, 4,                   "Usage: ./detab inputfile outputfile tab_interval (optional)\n")) {
    exit(1);
  }
  
        // process input file to remove tabs and substitute spaces
  int c;
  char maxspaces[MAX_TAB_INTERVAL + 1];
  char spaces[MAX_TAB_INTERVAL + 1];
  memset(maxspaces, ' ', sizeof(maxspaces));

  int bytes_written = 0;
  while ((c = fgetc(fin)) != EOF) {
    if (c != '\t') {
      fputc(c, fout);
      ++bytes_written;
    } else {
      int bytes_to_tab = tab_interval - (bytes_written % tab_interval);
      strncpy(spaces, maxspaces, bytes_to_tab);
      spaces[bytes_to_tab] = '\0';
      fputs(spaces, fout);
      bytes_written += strlen(spaces);
    }
  }
  
  closefiles(2, fin, fout);  // must say number of files
  
  return 0;
}
