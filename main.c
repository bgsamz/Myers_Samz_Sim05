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

/*
 *  Name:        main
 *  Description: Error checks all inputs, loads the configuration and programs
 *               into memory, and runs the programs after sorting them into the
 *               correct order.
 */
int main(int argc, char * argv[])
{

    int configMessage, programMessage;
    int numPrograms, numActions;
    int count;
    struct Config config;
    struct PCB * programPCBs;
    struct PCB * firstPCB;
    struct Action * actions;
    struct Action ** programs;
    char outputStr[128];

    // Check if there is less than or more than one argument passed
    if (argc != 2)
    {
        reportError(0);
        return 0;
    }

    // Print starting simulator message and loading config message
    printf("\n");
    printf("Operating System Simulator\n");
    printf("==========================\n");
    printf("\n");
    printf("Loading configuration file\n");

    // Load the configuration file
    configMessage = readConfig(argv[1], &config);

    // Check the configuration file
    if (configMessage != 0)
    {
        reportError(configMessage);
        return 0;
    }

    // Check the version number
    if (config.version != 4)
    {
        reportError(13);
        return 0;
    }

    // If file is the only output, print the file log message
    if (strcmp(config.logTo, "File") == 0)
    {
        printf("\n");
        printf("Logging all future output to %s\n", config.logPath);
        printf("\n");
    }

    // Initialize the file output
    output(config, "Initialize");

    // Print loading meta-data message
    output(config, "Loading meta-data file\n");
    output(config, "==========================\n");
    output(config, "\n");

    // Allocate memory for the program actions and retrieve them
    actions = malloc(MAX_ACT * sizeof(struct Action));
    numActions = 0;
    programMessage = readProgram(config.filePath, actions, &numActions);

    // Check the program file
    if (programMessage != 0)
    {
        reportError(programMessage + 8);
        return 0;
    }

    // Print starting sim message
    output(config, "Begin Simulation\n");

    // Initialize system timer
    output(config, "Time:");
    output(config, systemTime(0));
    output(config, " System Start\n");

    memset(outputStr, '\0', 128);

    // Print number of programs message
    strcat(outputStr, outputTime(config));
    strcat(outputStr, " OS: Detecting number of programs\n");
    output(config, outputStr);

    // Allocate memory for an array of Action array pointers
    programs = malloc(10 * sizeof(struct Action *));

    for (count = 0; count < 10; count++)
    {
        programs[count] = malloc(MAX_ACT * sizeof(struct Action));
    }

    // Split the programs
    numPrograms = splitPrograms(actions, numActions, programs);

    memset(outputStr, '\0', 128);

    // Print PCB Creation message
    strcat(outputStr, outputTime(config));
    strcat(outputStr, " OS: Begin PCB Creation\n");
    output(config, outputStr);

    // Allocate memory for program PCBs and initialize them
    programPCBs = malloc(numPrograms * sizeof(struct PCB));

    for (count = 0; count < numPrograms; count++)
    {
        initializePCB(&programPCBs[count], programs[count]);
    }

    firstPCB = convertToLinkedList(programPCBs, numPrograms);

    memset(outputStr, '\0', 128);

    // Print Initialization message
    strcat(outputStr, outputTime(config));
    strcat(outputStr, " OS: Processes initialized in New state\n");
    output(config, outputStr);

    // Run the programs
    runPrograms(firstPCB, numPrograms, config);

    // Print ending sim message
    output(config, "\n");
    output(config, "End Simulation\n");
    output(config, "==========================\n");
    output(config, "\n");

    // Write the log file output
    output(config, "Finalize");

    // End program
    return 0;

}

////////////////////////////////////////////////////////////////
//                      Helper Functions                      //
// Functions that assist in the running of the main function, //
//      but do not belong in the helperFunctions.c file.      //
//                Listed in alphabetical order                //
////////////////////////////////////////////////////////////////

struct PCB * convertToLinkedList(struct PCB * programPCBs, int numPrograms)
{
    int count;
    struct PCB * firstPCB = (struct PCB *) malloc(sizeof(struct PCB));
    struct PCB * currentPCB = &programPCBs[0];
    struct Action * firstAction = (struct Action *) malloc(sizeof(struct Action));
    struct Action * currentAction;

    firstPCB = &programPCBs[0];
    firstPCB->prevPCB = NULL;
    currentPCB = firstPCB;

    for (count = 1; count < numPrograms; count++)
    {
        currentPCB->nextPCB = (struct PCB *) malloc(sizeof(struct PCB));
        currentPCB->nextPCB = &programPCBs[count];
        currentPCB->nextPCB->prevPCB = currentPCB;
        currentPCB = currentPCB->nextPCB;
        currentPCB->nextPCB = NULL;
    }

    count = 0;
    currentPCB = firstPCB;

    while (currentPCB != NULL)
    {
        firstAction = &currentPCB->program[0];
        currentAction = firstAction;
        currentPCB->processNum = firstAction->processNum;

        for (count = 1; count < currentPCB->numActions; count++)
        {
            currentAction->nextAction = (struct Action *) malloc(sizeof(struct Action));
            currentAction->nextAction = &currentPCB->program[count];
            currentAction = currentAction->nextAction;
            currentAction->nextAction = NULL;
        }

        currentPCB->program = firstAction;
        currentPCB = currentPCB->nextPCB;
    }

    return firstPCB;
}

/*
 *  Name:        initializePCB
 *  Description: Used to initialize the PCB of a new program. Assigns all the
 *               paremeters to their correct locations, and sets the PCB state
 *               to New.
 */
void initializePCB(struct PCB * pcb, struct Action * actions)
{

    int numAct;

    // Set the process state to New and assign the actions
    strcpy(pcb -> state, "New");
    pcb -> program = actions;

    // Initialize the number of actions
    numAct = 0;

    // Count the number of actions
    while(1)
    {

        if (strcmp(actions[numAct].opString, "end") != 0)
        {
            numAct++;
        }
        else
        {
            numAct++;
            break;
        }

    }

    // Assign the counted value to the number of actions
    pcb -> numActions = numAct;

}

/*
 *  Name:        splitPrograms
 *  Description: Takes in all the actions from the program input file and splits
 *               them into seperate programs, and places the action arrays into
 *               the destination array. Returns the number of programs detected.
 */
int splitPrograms(struct Action * acts, int numActs, struct Action ** programs)
{

    int index1, index2;
    int count, started;

    // Initialize index variables and program started variable
    index1 = 0;
    index2 = 0;
    started = 0;

    // Loop through each action in the action array
    for (count = 0; count < numActs; count++)
    {

        // If you are currently adding to a program
        if (started == 1)
        {

            // Set the process number and add the action
            acts[count].processNum = index1;
            programs[index1][index2++] = acts[count];

        }

        // If the current action is the start to a program
        if (
            (acts[count].comLetter == 'A') &
            (strcmp(acts[count].opString, "start") == 0)
           )
        {

            // Set the process number add the action and mark the program start
            acts[count].processNum = index1;
            programs[index1][index2++] = acts[count];
            started = 1;

        }

        // If the current action is the end to a program
        else if (
                 (acts[count].comLetter == 'A') &
                 (strcmp(acts[count].opString, "end") == 0)
                )
        {

            // Set the process number add the action and mark the program end
            acts[count].processNum = index1;
            programs[index1][index2++] = acts[count];
            index1++;
            index2 = 0;
            started = 0;

        }

    }

    // Return the program count
    return index1;

}
