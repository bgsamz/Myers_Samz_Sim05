// Precompiler directives ////////////////////////
#ifndef TIMER_C
#define TIMER_C

#include "timer.h"

/*
 *  Name:        wait
 *  Description: Takes in a number of milliseconds and pauses the program for
 *               that number of milliseconds.
 */
void waitTime(int duration)
{
  struct timeval start;
  long int startSec, startMilSec, endSec, endMilSec;

  // Get the start time
  gettimeofday(&start, NULL);

  // Set the start and end time seconds and milliseconds
  startSec = start.tv_sec;
  endSec = startSec + (duration / 1000);

  startMilSec = start.tv_usec;
  endMilSec = startMilSec + ((duration % 1000) * 1000);

  // If the milliseconds go over a whole second,
  if (endMilSec > 999999)
  {
      endMilSec = endMilSec - 1000000;
      endSec = endSec + 1;
  }

  // Loop till the seconds match
  while (startSec < endSec)
  {
      gettimeofday(&start, NULL);
      startSec = start.tv_sec;
  }

  // Loop till the milliseconds match
  while (startMilSec < endMilSec)
  {
      gettimeofday(&start, NULL);
      startMilSec = start.tv_usec;
  }


  return;
}

/*
 *  Name:
 *  Description: A wrapper function that allows the wait function to be ran from
 *               within a pthread_create. Simply cast the void pointer to an
 *               int pointer, and then passes the value pointed to into wait.
 */
void * threadWait(void * threadStructPT)
{
    struct ThreadStruct * threadStruct;
    int duration;
    char * processNumber;
    char outputStr[128];

    memset(outputStr, '\0', 128);

    // Convert the void pointer to an int pointer
    threadStruct = (struct ThreadStruct *) threadStructPT;

    processNumber = intToString(threadStruct->currAct.processNum);
    duration = (threadStruct->currAct.cycleTime) * (threadStruct->config.ioTime);

    // Pass the value of the pointer to wait and return NULL
    waitTime(duration);

    strcat(outputStr, outputTime(threadStruct->config));
    strcat(outputStr, outputProcessNum(threadStruct->config, processNumber));
    strcat(outputStr, threadStruct->currAct.opString);
    strcat(outputStr, " end\n");
    output(threadStruct->config, outputStr);

    memset(outputStr, '\0', 128);

    strcat(outputStr, outputTime(threadStruct->config));
    strcat(outputStr, outputProcessNum(threadStruct->config, processNumber));
    strcat(outputStr, " set in READY state\n");
    output(threadStruct->config, outputStr);

    strcpy(threadStruct->currPro->state, "Ready");

    return NULL;

}

/*
 *  Name:        systemTime
 *  Description: Used to keep track of the simulator time. Initialize the time
 *               by passing in a zero for the parameter, and get the current
 *               system time by passing in any other integer.
 */
char * systemTime(int code)
{

    struct timeval startTime;
    struct timeval sysTime;
    static long int startSec;
    static long int startMilSec;
    long int seconds, milSeconds;
    char * output;

    output = malloc(STR_SML);

    // If the code parameter is zero, initialize the system time
    if (code == 0)
    {

        gettimeofday(&startTime, NULL);
        startSec = startTime.tv_sec;
        startMilSec = startTime.tv_usec;
        return "  0.000000";

    }

    // If the code parameter is anything else, get the current system time
    else
    {

        // Find the current time
        gettimeofday(&sysTime, NULL);

        // Substract it from the time of initialization
        seconds = sysTime.tv_sec - startSec;
        milSeconds = sysTime.tv_usec - startMilSec;

        // Check for negative miliseconds
        if (milSeconds < 0.0)
        {

            // Make miliseconds positive and subtract one from the seconds
            milSeconds = milSeconds + 1000000;
            seconds = seconds - 1;
        }

        // Format the output
        sprintf(output, "%10.6f", seconds + (milSeconds / 1000000.0));

        // Remove the leading zeros if necessary
        if (output[0] == '0')
        {
            output[0] = ' ';

            if (output[1] == '0')
            {
                output[1] = ' ';
            }

        }

        // Return final output
        return output;

    }

}

#endif
