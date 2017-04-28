/*
 * Objective #1 was to reformat all code to use header files that contained
 * all necessary includes, functions, and constant definitions.
 * This file accomplishes that goal, as can be seen below.
 */

// Precompiler directives ////////////////////////
#ifndef OUT_H
#define OUT_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "timer.h"
#include "structures.h"

void output(struct Config config, char * input);
char * outputProcessNum(struct Config config, char * input);
char * outputTime(struct Config config);

#endif
