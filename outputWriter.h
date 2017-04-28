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