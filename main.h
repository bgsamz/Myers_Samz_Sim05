// Precompiler directives ////////////////////////
#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>   // I/O
#include <stdlib.h>  // Malloc
#include <string.h>  // String Operations
#include "configReader.h"
#include "errors.h"
#include "helperFunctions.h"
#include "outputWriter.h"
#include "programReader.h"
#include "programRunner.h"
#include "structures.h"
#include "timer.h"

// Additional constants not found in structures.h
#define MAX_ACT 200

// Function Declarations
int getProgramLength(struct PCB pcb);
void initializePCB(struct PCB * pcb, struct Action * actions);
void output(struct Config config, char * input);
char * outputTime(struct Config config);
char * outputProcessNum(struct Config config, char * input);
void sortPrograms(struct Config config, struct PCB * programs, int numPrograms);
int splitPrograms(struct Action * acts, int numActs, struct Action ** programs);

struct PCB * convertToLinkedList(struct PCB * programPCBs, int numPrograms);

#endif