// Precompiler directives ////////////////////////
#ifndef TIMER_H
#define TIMER_H

#include <sys/time.h> // Time of day
#include <stdio.h>    // SprintF
#include <string.h>
#include <stdlib.h>   // Malloc
#include "helperFunctions.h"
#include "outputWriter.h"
#include "structures.h"

void   waitTime(int duration);
void * threadWait(void * threadStructPT);
char * systemTime(int code);

#endif