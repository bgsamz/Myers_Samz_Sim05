// Precompiler directives ////////////////////////
#ifndef ERR_C
#define ERR_C

#include "errors.h"

/*
 *  Name:        reportError
 *  Description: Takes in an integer code and prints out the error that
 *               corresponds to that code.
 */
void reportError(int code)
{

    printf("\n");

    /////////////////////
    // Argument Errors //
    /////////////////////

    // Invalid number of program arguments
    if (code == 0)
    {

        printf("    Error: Single config file argument expected\n");
        printf("    Example: ./sim03 config1.cnf\n");
        printf("    Program aborted\n");

    }

    ///////////////////////////////
    // Configuration File Errors //
    ///////////////////////////////

    // Config file could not be located
    else if (code == 1)
    {

        printf("    Error: Config file could not be located\n");
        printf("    Program aborted\n");

    }

    // Invalid version / phase number
    else if (code == 2)
    {

        printf("    Error: Invalid version/phase number detected\n");
        printf("    Value should be between or equal to 0 through 10\n");
        printf("    Program aborted\n");

    }

    // Invalid CPU scheduling code
    else if (code == 3)
    {

        printf("    Error: Invalid CPU scheduling code detected\n");
        printf("    Value should be one of the following:\n");
        printf("        NONE,   FCFS-N\n");
        printf("        SJF-N,  SRTF-P\n");
        printf("        FCFS-P, RR-P\n");
	printf("    Make sure there is no trailing whitespace after the code\n");
        printf("    Program aborted\n");

    }

    // Invalid quantum time
    else if (code == 4)
    {

        printf("    Error: Invalid quantum time detected\n");
        printf("    Value should be between or equal to 0 through 100\n");
        printf("    Program aborted\n");

    }

    // Invalid memory amount
    else if (code == 5)
    {

        printf("    Error: Invalid memory amount detected\n");
        printf("    Value should be between or equal to 0 through 1,048,576\n");
        printf("    Program aborted\n");

    }

    // Invalid processor cycle time
    else if (code == 6)
    {

        printf("    Error: Invalid processor cycle time detected\n");
        printf("    Value should be between or equal to 1 through 1,000\n");
        printf("    Program aborted\n");

    }

    // Invalid I/O cycle time
    else if (code == 7)
    {

        printf("    Error: Invalid I/O cycle time detected\n");
        printf("    Value should be between or equal to 1 through 10,000\n");
        printf("    Program aborted\n");

    }

    // Invalid log location
    else if (code == 8)
    {

        printf("    Error: Invalid log location\n");
        printf("    Log location should be either Monitor, File, or Both\n");
        printf("    Program aborted\n");

    }

    /////////////////////////
    // Program File Errors //
    /////////////////////////

    // Program file could not be found
    else if (code == 9)
    {

        printf("    Error: Program file could not be located\n");
        printf("    Program loading aborted\n");

    }

    // Invalid start to program
    else if (code == 10)
    {

        printf("    Error: Invalid start to program file\n");
        printf("    Program loading aborted\n");

    }

    // Invalid end to program
    else if (code == 11)
    {

        printf("    Error: Invalid end to program file\n");
        printf("    Program loading aborted\n");

    }

    // Invalid program action syntax
    else if (code == 12)
    {

        printf("    Error: Invalid action syntax found\n");
        printf("    Program loading aborted\n");

    }

    //////////////////////////////
    // Simulator Version Errors //
    //////////////////////////////

    // Invalid version number
    else if (code == 13)
    {

        printf("    Error: Invalid version/phase number detected\n");
        printf("    Version/phase must match current sim version: 3\n");
        printf("    Program aborted\n");

    }

    printf("\n");

}

#endif