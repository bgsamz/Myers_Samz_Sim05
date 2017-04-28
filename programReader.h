/*
 * Objective #1 was to reformat all code to use header files that contained
 * all necessary includes, functions, and constant definitions.
 * This file accomplishes that goal, as can be seen below.
 */

// Precompiler directives ////////////////////////
#ifndef PRGREAD_H
#define PRGREAD_H

#include <stdio.h>  // I/O
#include <stdlib.h> // Malloc
#include <string.h> // String Operations
#include "structures.h"
#include "helperFunctions.h"

// Function Declarations
char * getNextAction(char * line);
int createAction(char * string, struct Action * data);
int readProgram(char fileName[50], struct Action * actions, int * numActions);

#endif
