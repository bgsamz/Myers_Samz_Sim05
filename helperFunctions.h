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