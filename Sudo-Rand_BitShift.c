/*
 * Miguel Calderon
 * CSC 381 UNIX w/ C
 * Professor O'Rourke
 * Date: 11/19/19
 * Last Modified 11/19/19
 */

//Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Constants
#define TRUE 1
#define FALSE 0
#define MAX_BITS 31
#define MAX_DIGITS 15

//Prototypes
int* getRands(int);                 // returns a runtime array of random values
unsigned int getNewSeed(unsigned int userNum, unsigned int tapNum); // no longer used
unsigned int getSize();             // get sized and validates size
void WriteToFile(int* randArr, unsigned int size, char* fileName);  // prints

int main(/*int argc, char *argv[]*/) {  // Argc counts # of inputs & Argv holds them

    // Command Line
    char tempStr[MAX_DIGITS];
    puts("Enter a string");
    scanf("%s", tempStr);
 //   printf("The value you entered was %s\n", /*argv[1]*/tempStr); //testing only

    //Variables
    unsigned int userNum;
    unsigned int genNum;        // holds generated seed
    unsigned int userTap;
    unsigned int size;          // hold size requested by user
    unsigned int leftMostBit;   // holds MSB
    unsigned int feedBackBit;
    unsigned int tapBit;
    int clean;                  // holds signed input value to be converted later
    int* randArr;               // pointer to generated array
    int tap;                    // holds signed input value to be converted later
    short whileValid=TRUE;
    short tapValid =TRUE;       // boolean to let program know if it should continue
    char fileName[] ="random.txt";  // holds filename
   // clean =atoi(argv[1]);
    clean =atoi(tempStr);                           // convert string to integer

    if(clean<1) {                                   // checks for negatives
        if(clean==0)                                // checks for 0
            puts("INVALID NUMBER");
        else
            puts("POSITIVE NUMBERS ONlY");
    }
    else {
       // printf("After Conversion=%d\n", clean);       //testing only
        userNum = (unsigned)clean;                  // keep data-types consistent
        srand(/*time(userNum)*/userNum);

        leftMostBit = (userNum >> MAX_BITS) & 1;    // gets MSB (most significant bit)
        feedBackBit = leftMostBit;                  // extra variable, simply for readability

        puts("Please enter in your taps (enter -1 when finished):");
        do {
            scanf("%d", &tap);
            if(( tap < 0) || tap > MAX_BITS) {          // checks for invalid taps

                whileValid = (short)FALSE;
                if(tap != -1)
                tapValid=(short)FALSE;
            }
            else {
                userTap = (unsigned)tap;                 // keeping data-types consistent
                tapBit = (userNum >> userTap) & 1;       // converts tap to bit
                feedBackBit = feedBackBit ^ tapBit;      // XOR previous F-bit with new one
                tapValid = (short)TRUE;
            }

        }while (whileValid ==(short)TRUE);

        if(tapValid==TRUE) {                        //only if taps were valid

            userNum = (userNum << 1);               // shift all bits left 1
            genNum = (userNum ^ feedBackBit);       // get new number
            printf("genNum=%d\n", genNum);        //testing only
            srand(genNum);                          //set new seed
            size = getSize();                       // returns size user enters
            randArr = getRands(size);               // generates random array
            WriteToFile(randArr, size,fileName );   // writes array to file
            free(randArr);                          // release memory

        } // end if invalid taps
    } // if command line argument valid

    return 0;
} // end main

int* getRands(int size) {
/*
 *PRE: a non instantiated array, size is needed
 *POST: a runtime created array
 *PURPOSE: to create an array of random values at runtime
 */
    int *rands;
    rands = (int*)malloc(sizeof(int) * size);       //allocate new array
    int i;
    for (i=0; i<size; ++i)                                 // for each element generate random #
        rands[i]=rand()%100;
    return rands;
}
/*
unsigned int getNewSeed(unsigned int userNum, unsigned int tap) {

    //PRE:
    //POST:
    //PURPOSE: NO PURPOSE FUNCTION REMOVED

    unsigned int leftMostBit;
    unsigned int feedBackBit;
    unsigned int tapBit;

    leftMostBit = (userNum >> MAX_BITS) & 1;
    feedBackBit = leftMostBit;                      // extra variable, simply for readability
    tapBit = (userNum >> tap) & 1;                  // converts tap to bit
    feedBackBit = feedBackBit ^ tapBit;             // XOR tap with feedback
    userNum = (userNum << 1);                       // shift per tap
    return (userNum ^ feedBackBit);                 // return new number
}
*/
unsigned int getSize() {
    /*
    *PRE:
    *POST:
    *PURPOSE:
    */
    unsigned int size;
    puts("How many random #'s would you like?");
    scanf("%d", &size);
    while (size < 0 || size > 1000000) {            //Check for invalid number
        if (size < 0) {
            printf("%d can't be NEGATIVE: Please re-enter a size\n", size);
        } else {
            printf("%d is INVALID: Please re-enter a size\n", size);
        }
        scanf("%d", &size);
    }
    return size;
}

void WriteToFile(int* randArr, unsigned int size, char* fileName) {
    /*
    *PRE:
    *POST:
    *PURPOSE:
    */
    FILE *din;                                              //declare pointer to file
    din = fopen(fileName, "w");                     //open file
    for (int i = 0; i < size; ++i) {
        fprintf(din, "%d\n", randArr[i]);          //print numbers
    } // end print
    fclose(din);                                           //close file
} // end WriteToFile()
