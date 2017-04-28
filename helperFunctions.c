#include <stdlib.h> // Malloc
#include <string.h> // String Operations
#include "structures.h"

/*
 *  Name:        findChar
 *  Description: Loops through a char array searching for a specific target
 *               char. Returns the index of the char if it is found, and -1 if
 *               it is not found.
 */
int findChar(char * string, char target)
{

    // Counter for loop
    int count;

    // Loop through every char in the string
    for (count = 0; count < strlen(string); count++)
    {

        // If the char is equal to our target, return count
        if (string[count] == target)
        {
            return count;
        }

    }

    // If the char is not found, return -1
    return -1;

}

/*
 *  Name:        intToString
 *  Description: Converts an integer into a character array. Current only works
 *               with values larger than or equal to 0, and smaller than 1000.
 */
char * intToString(int input)
{

    char * newString;

    // Allocate memory to the new string
    newString = malloc(STR_SML);

    // If it is a single digit number
    if (input < 10)
    {
        newString[0] = input + '0';
        newString[1] = '\0';
    }

    // If it is a two digit number
    else if (input < 100)
    {
        newString[0] = ((input - (input % 10)) / 10) + '0';
        newString[1] = (input % 10) + '0';
        newString[2] = '\0';
    }

    // If it is a three digit number
    else if (input < 1000)
    {
        newString[0] = ((input - (input % 100)) / 100) + '0';
        newString[1] = ((input - (input % 10) - (input - (input % 100))) / 10) + '0';
        newString[2] = (input % 10) + '0';
        newString[3] = '\0';
    }

    // Return the new string
    return newString;

}

/*
 *  Name: stringToInt
 *  Description: Converts a char array to an integer. Example: {'7', '1', '4'}
 *               would be converted into an integer 714.
 */
int stringToInt(char * string)
{

    int count, digit, answer;

    // Initialize variables for loop and final answer
    digit = 1;
    answer = 0;

    // Loop through array
    for (count = strlen(string) - 1; count >= 0; count--)
    {

        // Convert char int, multiple it by the digit place, add to total
        answer += (string[count] - '0') * digit;

        // Increment digit to the next place
        digit *= 10;
    }

    // Return the final total
    return answer;

}

/*
 *  Name:        substring
 *  Description: Returns a subsection of a character array derived from the
 *               start and end integer parameters passed to it.
 */
char * substring(char * string, int start, int end)
{

    int count;
    int index;
    char * newString;

    // Initialize loop counter, and char array
    index = 0;
    newString = malloc(STR_LRG);

    // Loop through input array, assign values to it
    for (count = start; count < end; count++)
    {
        newString[index] = string[count];
        index++;
    }

    // Mark the end of the string in the array
    newString[index] = '\0';

    // Return the final new array
    return newString;

}
