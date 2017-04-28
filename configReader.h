// Precompiler directives ////////////////////////
#ifndef CFG_H
#define CFG_H

#include <stdio.h>  // I/O
#include <stdlib.h> // Malloc
#include <string.h> // String Operations
#include "structures.h"
#include "helperFunctions.h"

int readConfig(char fileName[50], struct Config * data);

#endif