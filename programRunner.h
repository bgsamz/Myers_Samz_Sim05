// Precompiler directives ////////////////////////
#ifndef PRGRUN_H
#define PRGRUN_H

#include <stdlib.h> // Malloc
#include <pthread.h> // Threads
#include <string.h>  // String Operations
#include "helperFunctions.h"
#include "outputWriter.h"
#include "structures.h"
#include "timer.h"

#include <stdio.h>

// Function declarations
void runPrograms(struct PCB * programPCBs, int numPrograms, struct Config config);
void runFCFS_N(struct PCB * programPCBs, int numPrograms, struct Config config);
void runSJF_N(struct PCB * programPCBs, int numPrograms, struct Config config);
void runFCFS_P(struct PCB * programPCBs, int numPrograms, struct Config config);
void runSRTF_P(struct PCB * programPCBs, int numPrograms, struct Config config);
void runRR_P(struct PCB * programPCBs, int numPrograms, struct Config config);
void runAction(struct PCB * currPro, struct Action * currAct, struct Config config);
void sortPrograms(struct Config config, struct PCB * programs, int numPrograms);
int getProgramLength(struct PCB pcb);

#endif