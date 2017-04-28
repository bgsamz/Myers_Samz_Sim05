// Precompiler directives ////////////////////////
#ifndef OUT_C
#define OUT_C

// Accomplishes objective #1 by reformatting code to use cleaner include
// statements and header files.
#include "outputWriter.h"

/*
 *  Name:        output
 *  Description: Checks if the input needs to be written to the file, and if it
 *               does, adds it to the static string. Then checks if the input
 *               needs to be printed to the monitor, and if it does, prints it.
 *               You can initialize the static string by passing the input
 *               "Initialize", and write to the file by passing the input
 *               "Finalize".
 */
void output(struct Config config, char * input)
{

    static char * fileContent;
    static int index;
    int count;
    FILE * file;

    // Check if the input needs to be written to a file
    if ((strcmp(config.logTo, "Both") == 0) |
        (strcmp(config.logTo, "File") == 0))
    {

        // If the output is being initialized
        if (strcmp(input, "Initialize") == 0)
        {

            // Initialize file content array and index counter
            fileContent = malloc(STR_LRG);
            index = 0;

            // End function
            return;

        }
        else if (strcmp(input, "Finalize") == 0)
        {
            // Open the file at the log path and write file content to it
            file = fopen(config.logPath, "w");
            fputs(fileContent, file);
            fclose(file);

            // End function
            return;

        }
        else
        {

            // Allocate more memory to the array
            fileContent = realloc(fileContent, strlen(fileContent) + STR_LRG);

            // Copy contents of input to the file content array
            for (count = 0; count < strlen(input); count++)
            {
                fileContent[index++] = input[count];
            }

        }

    }

    // Check if the input needs to be printed
    if ((strcmp(config.logTo, "Monitor") == 0) |
        (strcmp(config.logTo, "Both") == 0))
    {

        if (strcmp(input, "Finalize") == 0)
        {
            return;
        }
        else
        {
            printf("%s", input);
        }

    }

}

/*
 *  Name:        outputProcessNum
 *  Description: Another wrapper function to make the main look less ugly.
 */
char * outputProcessNum(struct Config config, char * input)
{
    char * returnStr = malloc(128);

    memset(returnStr, '\0', 128);

    strcat(returnStr, " Process ");
    strcat(returnStr, input);
    strcat(returnStr, ", ");

    return returnStr;
}

/*
 *  Name:        outputTime
 *  Description: Just a wrapper function to condence lines of code later in the
 *               main function.
 */
char * outputTime(struct Config config)
{
    char * returnStr = malloc(128);

    memset(returnStr, '\0', 128);

    strcat(returnStr, "Time:");
    strcat(returnStr, systemTime(1));

    return returnStr;
}

#endif
