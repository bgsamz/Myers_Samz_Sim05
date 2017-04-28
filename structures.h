// Make sure not to compile structures more than once
#ifndef STRUCTURES_H
#define STRUCTURES_H

// Constants to be used across multiple files
#define STR_SML 32
#define STR_LRG 128

// Structure used to hold the data of an individual action from a program
struct Action
{

    char comLetter;
    char opString[16];
    int  cycleTime;
    int  processNum;
    struct Action * nextAction;
};

// Structure used to hold all necessary data read in from a configuration file
struct Config
{

    char     filePath[64];
    char     schCode[16];
    char     logTo[16];
    char     logPath[64];
    int      version;
    int      quanTime;
    int      pTime;
    int      ioTime;
    long int memAvail;

};

// Structure used to hold all the information relating to a single program
struct PCB
{

    char   state[16];
    int    numActions;
    struct Action * program;
    struct PCB * nextPCB;
};

// Structure to be used for holding information to be passed into a thread.
struct ThreadStruct
{
    struct PCB * currPro;
    struct Action currAct;
    struct Config config;
};

#endif
