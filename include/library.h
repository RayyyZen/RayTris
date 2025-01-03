#ifndef LIBRARY_H
#define LIBRARY_H

#define _POSIX_C_SOURCE 200809L
//To define the CLOCK_REALTIME variable used in player movement function
#include <ncurses.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define BOXLINES 28
#define BOXCOLUMNS 100

void initializeColor();

#endif