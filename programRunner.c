// Precompiler directives ////////////////////////
#ifndef PRGRUN_C
#define PRGRUN_C

// Accomplishes objective #1 by reformatting code to use cleaner include
// statements and header files.
#include "programRunner.h"

/*
 *  Name:        runPrograms
 *  Description: Checks the CPU scheduling code and calls the corresponding
 *               function to run the programs.
 */
void runPrograms(struct PCB * programPCBs, int numPrograms, struct Config config)
{

    char * schCode;

    // Get the code
    schCode = config.schCode;

    // Run the corresponding function
    if (strcmp(schCode, "FCFS-N") == 0)
    {
        runFCFS_N(programPCBs, numPrograms, config);
    }
    else if (strcmp(schCode, "SJF-N") == 0)
    {
        runSJF_N(programPCBs, numPrograms, config);
    }
    else if (strcmp(schCode, "FCFS-P") == 0)
    {
        runFCFS_P(programPCBs, numPrograms, config);
    }
    else if (strcmp(schCode, "SRTF-P") == 0)
    {
        runSRTF_P(programPCBs, numPrograms, config);
    }
    else
    {
        runRR_P(programPCBs, numPrograms, config);
    }

}

/*
 *  Name:        runFCFS_N
 *  Description: Loops through each program and runs them in the order that they
 *               were found in the file.
 */
void runFCFS_N(struct PCB * programPCBs, int numPrograms, struct Config config)
{
    struct PCB * currPro;
    struct Action * currAction;

    currPro = programPCBs;

    // Loop through each program
    while (currPro != NULL)
    {
        currAction = currPro->program;

        // Loop through each action in that program
        while (currAction != NULL)
        {

            while (strcmp(currPro->state, "Blocked") == 0)
            {
              // Loop until not blocked.
            }

            // Run the next action in the program
            runAction(currPro, currAction, config);

            currAction = currAction->nextAction;
        }

        currPro = currPro->nextPCB;
    }

}

/*
 *  Name:        runSJF_N
 *  Description: Sorts the programs in order of shortest time first and then
 *               runs them just like FCFS-N.
 */
void runSJF_N(struct PCB * programPCBs, int numPrograms, struct Config config)
{
    // Accomplishes object #2, see sortPCB function.
    sortPCB( programPCBs, numPrograms, config );

    // Now that the programs are sorted, run them like FCFS-N
    runFCFS_N(programPCBs, numPrograms, config);

}

/*
 *  Name:        runFCFS_P
 *  Description: Runs the programs using the first come first serve preemptive
 *               CPU scheduling code.
 */
void runFCFS_P(struct PCB * programPCBs, int numPrograms, struct Config config)
{
    struct PCB * currPro = programPCBs;
    struct PCB * prevPro = NULL;
    struct PCB * firstPro = programPCBs;
    char outputStr[128];

    // Loop through each program and set it to ready state
    while (currPro != NULL)
    {
        strcpy(currPro->state, "Ready");
        currPro = currPro->nextPCB;
    }

    currPro = programPCBs;

    memset(outputStr, '\0', 128);

    // Output the ready message
    strcat(outputStr, outputTime(config));
    strcat(outputStr, " OS: All processes now set in READY state\n");
    output(config, outputStr);

    // While not all the programs are done
    while (firstPro != NULL)
    {
        currPro = firstPro;
        // Loop through each program
        while (currPro != NULL)
        {
            // If it is not blocked state or exit state
            if ((strcmp(currPro->state, "Blocked") != 0) &&
                (strcmp(currPro->state, "Exit") != 0))
            {

                if ((prevPro == NULL) ||
                    (prevPro->processNum != currPro->processNum))
                {
                    if ((prevPro != NULL) &&
                        (strcmp(prevPro->state, "Running") == 0))
                    {

                        memset(outputStr, '\0', 128);

                        // Output the ready message and set the program in ready state
                        strcat(outputStr, outputTime(config));
                        strcat(outputStr, outputProcessNum(config, intToString(prevPro->processNum)));
                        strcat(outputStr, " set in READY state\n");
                        output(config, outputStr);

                        strcpy(prevPro->state, "Ready");
                    }
                    memset(outputStr, '\0', 128);

                    // Output which program is selected
                    strcat(outputStr, "\n");
                    strcat(outputStr, outputTime(config));
                    strcat(outputStr, " OS: FCFS-P selects");
                    strcat(outputStr, outputProcessNum(config, intToString(currPro->processNum)));
                    strcat(outputStr, "\n");
                    output(config, outputStr);

                    memset(outputStr, '\0', 128);

                    // Output the running state message
                    strcat(outputStr, outputTime(config));
                    strcat(outputStr, outputProcessNum(config, intToString(currPro->processNum)));
                    strcat(outputStr, " set in RUNNING state\n");
                    output(config, outputStr);

                    strcpy(currPro->state, "Running");
                }

                // Run an action of the program and add to the counter
                runAction(currPro, currPro->program, config);
                currPro->program = currPro->program->nextAction;
                prevPro = currPro;
                break;
            }
            currPro = currPro->nextPCB;
        }

        while ((firstPro != NULL) && (strcmp(firstPro->state, "Exit") == 0))
        {
            firstPro = firstPro->nextPCB;
        }
    }
}

/*
 * Goal to fix SRTF-P (goal #2), semi accomplished. SRTF-P still needs to be
 * fixed by implementing the sortPCB function into the code, then running
 * FCFS-N in the same general manner, looping and sorting each time.
 */

/*
 *  Name:        runSRTF_P
 *  Description: Sorts the programs in order of shortest time first and then
 *               runs them and returns them to queue based on remaining time
 */
void runSRTF_P(struct PCB * programPCBs, int numPrograms, struct Config config)
{
    int counter = 0;
    int doneCount = 0;
    int prevPro = -1;
    int actionsCompleted[numPrograms];
    struct PCB * currPro = (struct PCB *) malloc(sizeof(struct PCB));
    int count, swap, saveNum;
    struct PCB tempProgram;
    char outputStr[128];

    // Save the number of programs, since bubble sort will reduce it
    saveNum = numPrograms;

    // Initialize swap to true
    swap = 1;

    // While Swaps are still occuring, sort
    while (swap == 1)
    {

        // Assume no swap has been made yet
        swap = 0;

        // Loop through each program and swap if necessary
        for (count = 0; count < numPrograms - 1; count++)
        {

            if (getProgramLength(programPCBs[count]) >
                getProgramLength(programPCBs[count + 1]))
            {

                tempProgram = programPCBs[count];
                programPCBs[count] = programPCBs[count + 1];
                programPCBs[count + 1] = tempProgram;

                // If a swap occurs, set swap to true
                swap = 1;

            }

        }

        numPrograms--;

    }

    // Set ations to reay state
    for (counter = 0; counter < saveNum; counter++)
    {
        actionsCompleted[counter] = 0;
        strcpy(programPCBs[counter].state, "Ready");
    }

    memset(outputStr, '\0', 128);

    strcat(outputStr, outputTime(config));
    strcat(outputStr, " OS: All processes now set in READY state\n");
    output(config, outputStr);

    // While all processes are not finished
    while (doneCount < saveNum)
    {
        doneCount = 0;

        // For each process in ready state
        for (counter = 0; counter < saveNum; counter++)
        {
            currPro = &programPCBs[counter];

            if ((strcmp(currPro->state, "Blocked") != 0) &&
                (strcmp(currPro->state, "Exit") != 0))
            {

            if (counter != prevPro)
            {
                // if execution is unfinished
                if (strcmp(programPCBs[prevPro].state, "Running") == 0)
                {
                  memset(outputStr, '\0', 128);

                  strcat(outputStr, outputTime(config));
                  strcat(outputStr, outputProcessNum(config, intToString(counter)));
                  strcat(outputStr, " set in READY state\n");
                  output(config, outputStr);

                  strcpy(programPCBs[prevPro].state, "Ready");
                }

                memset(outputStr, '\0', 128);

                strcat(outputStr, "\n");
                strcat(outputStr, outputTime(config));
                strcat(outputStr, " OS: SRTF-P selects");
                strcat(outputStr, outputProcessNum(config, intToString(counter)));
                strcat(outputStr, "\n");
                output(config, outputStr);

                memset(outputStr, '\0', 128);

                strcat(outputStr, outputTime(config));
                strcat(outputStr, outputProcessNum(config, intToString(counter)));
                strcat(outputStr, " set in RUNNING state\n");
                output(config, outputStr);

                strcpy(currPro->state, "Running");
            }

            // run the next action in the queue
            runAction(currPro, &currPro->program[actionsCompleted[counter]], config);
            actionsCompleted[counter]++;
            prevPro = counter;
            break;
        }
    }

    for (counter = 0; counter < saveNum; counter++)
    {
      if (strcmp(programPCBs[counter].state, "Exit") == 0)
      {
        doneCount++;
      }
    }
  }
}

/*
 * Completely rewritten implementation of runRR_P satisfies goal #4.
 * Goal was to create more efficient code using the new linkedlist structure.
 * This was done by modifying the original code to use a linked list as
 * opposed to an array, and borrowing elements from the implementation of
 * FCFS-P while writing.
 * Goal #4 satisfied here.
 */


/*
 *  Name:        runRR_P
 *  Description: Runs the program using the round robin CPU scheduling code.
 *               this allows each program to run for the quantum time before
 *               moving on to the next program. This repeats until all programs
 *               have completed.
 */
void runRR_P(struct PCB * programPCBs, int numPrograms, struct Config config)
{

    struct PCB * currPro = programPCBs;
    struct PCB * firstPro = programPCBs;
    char outputStr[128];
    int remCycles;

    // Loop through each program and set it to ready state
    while (currPro != NULL)
    {
        strcpy(currPro->state, "Ready");
        currPro = currPro->nextPCB;
    }

    currPro = programPCBs;

    memset(outputStr, '\0', 128);

    // Output the ready message
    strcat(outputStr, outputTime(config));
    strcat(outputStr, " OS: All processes now set in READY state\n");
    output(config, outputStr);

    while(firstPro != NULL)
    {
        // Loop through each program
        while (currPro != NULL)
        {
            // If the program has not finished running or not blocked
            if ((strcmp(currPro->state, "Blocked") != 0) &&
                (strcmp(currPro->state, "Exit") != 0))
            {
                // Place the program back into running state, unless its new
                if (strcmp(currPro->state, "Ready") != 0)
                {
                    memset(outputStr, '\0', 128);

                    strcat(outputStr, outputTime(config));
                    strcat(outputStr, " OS:");
                    strcat(outputStr, outputProcessNum(config, intToString(currPro->processNum)));
                    strcat(outputStr, "set in Running state\n");
                    output(config, outputStr);

                    strcpy(currPro->state, "Running");
                }

                // Get the quantum time from the config
                remCycles = config.quanTime;

                // Run the program for the quantum time
                while (remCycles > 0)
                {
                    // Run the action
                    runAction(currPro, currPro->program, config);

                    while (strcmp(currPro->state, "Blocked") == 0)
                    {
                      //Wait until not blocked.
                    }

                    // If its not a memory operation, subtract its cycle time
                    if (currPro->program->comLetter != 'M')
                    {
                        remCycles -= currPro->program->cycleTime;
                    }

                    // If end of program is reached set remaining cycles to zero
                    if (strcmp(currPro->program->opString, "end") == 0)
                    {
                        remCycles = 0;
                    }

                    // Go to next action
                    currPro->program = currPro->program->nextAction;

                    if (strcmp(currPro->state, "Blocked") == 0)
                    {
                      break;
                    }

                }

                // If the program didn't finish, place it into ready state
                if (strcmp(currPro->state, "Exit") != 0)
                {
                    memset(outputStr, '\0', 128);

                    strcat(outputStr, outputTime(config));
                    strcat(outputStr, " OS:");
                    strcat(outputStr, outputProcessNum(config, intToString(currPro->processNum)));
                    strcat(outputStr, "set in Ready state\n");
                    output(config, outputStr);

                    // Set the process back into ready state after its time is up
                    strcpy(currPro->state, "Ready");
                }

                output(config, "\n");

            }
            currPro = currPro->nextPCB;
        }


        while ((firstPro != NULL) && (strcmp(firstPro->state, "Exit") == 0))
        {
            firstPro = firstPro->nextPCB;
        }
        currPro = firstPro;
    }

}

/*
 * Assists in accomplishing goal #2, this sort function is needed to
 * ensure that SRTF-P is sorted and runs properly everytime.
 */

/*
 *  Name:        runAction
 *  Description: Runs a single action of a program. If the action is a start/end
 *               action, it placed the PCB into running or exit state. If the
 *               action is an I/O operation it runs on its own thread. All other
 *               actions are ran normally.
 */
void runAction(struct PCB * currPro, struct Action * currAct, struct Config config)
{
    char outputStr[128];
    char * processNumber;
    int waitNum;
    pthread_t thread;
    struct ThreadStruct * threadStruct = (struct ThreadStruct *) malloc(sizeof(struct ThreadStruct));

    threadStruct->currPro = currPro;
    threadStruct->currAct = *currAct;
    threadStruct->config = config;

    // Get the process number
    processNumber = intToString(currAct->processNum);

    memset(outputStr, '\0', 128);

    // State the time of the action starting
    strcat(outputStr, outputTime(config));

    // If the action is a Program Start or End action
    if (currAct->comLetter == 'A')
    {

        // If the program is in running state
        if (strcmp(currAct->opString, "end") == 0)
        {
            strcat(outputStr, " OS:");
            strcat(outputStr, outputProcessNum(config, processNumber));
            strcat(outputStr, "set in Exit state\n");
            output(config, outputStr);

            // Put the program in the Exit state
            strcpy(currPro -> state, "Exit");
        }

        // If the program is in new, ready, or blocked state
        else
        {
            strcat(outputStr, " OS:");
            strcat(outputStr, outputProcessNum(config, processNumber));
            strcat(outputStr, "set in Running state\n");
            output(config, outputStr);

            // Put the program in Running state
            strcpy(currPro -> state, "Running");
        }
    }

    // If the action is a memory action
    else if (currAct->comLetter == 'M')
    {

        // Output the correct memory message
        if (strcmp(currAct->opString, "allocate") == 0)
        {
            strcat(outputStr, outputProcessNum(config, processNumber));
            strcat(outputStr, "memory management allocate action\n");
            output(config, outputStr);
        }
        else
        {
            strcat(outputStr, outputProcessNum(config, processNumber));
            strcat(outputStr, "memory management access action\n");
            output(config, outputStr);
        }

    }

    // If the action is a Run action or an I/O action
    else
    {

        // Output the process
        strcat(outputStr, outputProcessNum(config, processNumber));
        strcat(outputStr, currAct->opString);
        strcat(outputStr, " start\n");
        output(config, outputStr);

        // If it is an I/O action
        if ((currAct->comLetter == 'I') || (currAct->comLetter == 'O'))
        {

            pthread_create(&thread, NULL, threadWait, (void *) threadStruct);

            memset(outputStr, '\0', 128);

            strcpy(currPro->state, "Blocked");
            strcat(outputStr, outputTime(config));
            strcat(outputStr, outputProcessNum(config, processNumber));
            strcat(outputStr, " set in BLOCKED state\n");
            output(config, outputStr);

            return;

        }

        // If it is a Run action
        else
        {

            // Wait the amount of cycles
            waitNum = currAct->cycleTime * config.pTime;
            waitTime(waitNum);

        }

        memset(outputStr, '\0', 128);

        // Output the end time
        strcat(outputStr, outputTime(config));
        strcat(outputStr, outputProcessNum(config, processNumber));
        strcat(outputStr, currAct->opString);
        strcat(outputStr, " end\n");
        output(config, outputStr);

    }

}

/*
 *  Name:        getProgramLength
 *  Description: Calculates and returns the total number of cycles in a program.
 *               Used when sorting program execution.
 */
int getProgramLength(struct PCB pcb)
{

    int count, numCycles;

    // Initialize the number of cycles
    numCycles = 0;

    // Loop through each action and add the number of cycles
    for (count = 0; count < pcb.numActions; count++)
    {

        if (pcb.program[count].comLetter != 'M')
        {
            numCycles += pcb.program[count].cycleTime;
        }

    }

    // Return the counted number of cycles
    return numCycles;

}

//---------------------------
// #2 Sort PCB using a linked
// list structure
//---------------------------
void sortPCB( struct PCB * programPCBs, int numPrograms, struct Config config )
{
    int count;
    struct PCB * tempProgram;
    struct PCB * currPro = programPCBs;

    if(numPrograms == 1)
    {
        return;
    }

    // Loop through each program and swap if necessary
    if (getProgramLength(*currPro) >
            getProgramLength(*currPro->nextPCB))
    {

        tempProgram = currPro->nextPCB;
        currPro->nextPCB = tempProgram->nextPCB;
        tempProgram->prevPCB = currPro->prevPCB;
        currPro->prevPCB = tempProgram;
        tempProgram->nextPCB = currPro;

        if ( tempProgram->prevPCB != NULL )
        {
            tempProgram->prevPCB->nextPCB = tempProgram;
        }

        currPro = tempProgram->nextPCB;

    }
    else
    {
        currPro = currPro->nextPCB;
    }

    numPrograms--;

    sortPCB(currPro, numPrograms, config);
}

#endif
