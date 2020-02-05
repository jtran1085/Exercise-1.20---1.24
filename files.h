//
//  files.h
//  detab
//
//  Created by William McCarthy on 032//20.
//  Copyright © 2020 William McCarthy. All rights reserved.
//

#ifndef files_h
#define files_h

#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>


bool open_io_files(int argc, const char* argv[], FILE** fin, FILE** fout,
                   int min_expected_argc, int max_expected_argc,
                   const char* usage);

void closefiles(int n, ...);

#endif /* files_h */
