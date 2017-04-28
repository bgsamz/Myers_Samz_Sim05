/*
 * Objective #1 was to reformat all code to use header files that contained
 * all necessary includes, functions, and constant definitions.
 * This file accomplishes that goal, as can be seen below.
 */

// Precompiler directives ////////////////////////
#ifndef HELP_H
#define HELP_H

#include <stdlib.h> // Malloc
#include <string.h> // String Operations
#include "structures.h"

int findChar(char * string, char target);
char * intToString(int input);
int stringToInt(char * string);
char * substring(char * string, int start, int end);

#endif
