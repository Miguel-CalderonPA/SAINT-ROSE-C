//Libraries
#include <stdio.h>

//Constants
#define MAX 99999
#define SIZE 5
#define TRUE_STATE 1
#define FALSE_STATE 0
#define MAX_STATE 2

//Prototypes
int Prompt(unsigned int*);                                              // takes in pointer of type unsigned int
unsigned int CountNumbers(unsigned int, unsigned int*);                 // takes in a pointer and a variable of unsigned int
void FillArray(unsigned int[],unsigned int,unsigned int, unsigned int); // takes an array address and 3 variables of unsigned int
void PrintCombination(unsigned int[], unsigned int*);                   // takes in an array address and a pointer of unsigned int
unsigned int SwitchaRoo(unsigned int);                                  // takes in variable of unsigned int

int main() {
    // variables
    unsigned int input[SIZE]={0};                                       // initialize array to 0's
    unsigned int factor=1, numCombinations=1;
    unsigned int code, count;

        if(Prompt(&code) == 1) {                                        // if valid input

           count = CountNumbers(code,&factor);                          // count numbers (basically check for 0's)
           FillArray(input,count,code,factor);                          // fills array and adjusts for leading 0's

                // handles states for digit 1
                for (int digit1 = FALSE_STATE; digit1 < MAX_STATE; ++digit1) {
                    if(digit1==TRUE_STATE) {
                        input[0] = SwitchaRoo(input[0]);                    //switch state
                    }
                    // handles states for digit 2
                    for (int digit2 = FALSE_STATE; digit2 < MAX_STATE; ++digit2) {
                        if(digit2==TRUE_STATE) {
                            input[1] = SwitchaRoo(input[1]);                //switch state
                        }
                        // handles states for digit 3
                        for (int digit3 = FALSE_STATE; digit3 < MAX_STATE; ++digit3) {
                            if(digit3==TRUE_STATE) {
                                input[2] = SwitchaRoo(input[2]);            //switch state
                            }
                            // handles states for digit 4
                            for (int digit4 = FALSE_STATE; digit4 < MAX_STATE; ++digit4) {
                                if(digit4==TRUE_STATE) {
                                    input[3] = SwitchaRoo(input[3]);        //switch state
                                }
                                // handles states for digit 5
                                for (int digit5 = FALSE_STATE; digit5 < MAX_STATE; ++digit5) {
                                    if(digit5==TRUE_STATE) {
                                        input[4] = SwitchaRoo(input[4]);
                                        PrintCombination(input, &numCombinations);  //switch state
                                    }
                                    else {
                                        PrintCombination(input, &numCombinations);
                                    }
                                } // end digit 5
                            } // end digit 4
                        } // end digit 3
                    } // end digit 2
                } // end digit
        } // if prompt is wrong

    return 0;
} // end main

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Prompt~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

int Prompt(unsigned int* code) {
/*
 * PRE: asks the user for data
 * POST: returns if data is valid
 * PURPOSE: to determine get and check data from user
 */
    puts("Enter in the security code?");
    scanf("%u", code);
    if (*code > (unsigned int)MAX) {                        // if code is > than the max
        puts("INVALID CODE");
        return 0;                                           //false
    } // end check
    else {
        puts("ACCESS GRANTED");
        return 1;                                           // else its true
    }
} // end prompt

//~~~~~~~~~~~~~~~~~~~~~~~~~FillArray~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

void FillArray(unsigned int input[],unsigned int count,unsigned int code, unsigned int factor){
    /*
    * PRE: take in an empty array the number of digits in array and values for the array
    * POST: returns a full array with code and adjusts for leading 0's
    * PURPOSE: to fill the array appropriately
    */
    unsigned int temp;
    unsigned int numDigits=0;

    if (count < 5) {                                                    // if leading 0's
        for (unsigned int j = 0; j < (SIZE - count); ++j) {
            numDigits++;                                                //skip over
        }
    }
    while (factor > 1) {
        factor = factor / 10;    //takes account of digit gain
        temp = (code / factor);    //easier ot read
        input[numDigits++] = temp; // fill array with digits
        code = code % factor;    //remainder of digits left

    }// end while put together
} // end fill array

//~~~~~~~~~~~~~~~~~~~~~~CountNumbers~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

unsigned int CountNumbers(unsigned int code, unsigned int* factor) {
    /*
    * PRE: takes in the code and default factor
    * POST: returns how large number is based on code and total digits
    * PURPOSE: to count the number of digits in the array
    */
    unsigned int temp;
    unsigned int count=0;
    temp = code;                //holder

    while (temp)            //while number isn't 0 (false)
    {
        temp = temp / 10;        //cuts off digit
        *factor = *factor * 10;    //takes account of digit loss
        count++;
    }//end while take apart

    return count;
} // end count numbers

//~~~~~~~~~~~~~~~~~~PrintCombination~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

void PrintCombination(unsigned int input[], unsigned int* numCombinations) {
    /*
    * PRE: needs an array and an active runtime counter
    * POST: prints out a combination and which iteration it is on
    * PURPOSE: to print out a combination with corresponding number
    */
    printf("Combination #%2u: ", *numCombinations);
    for (int i = 0; i < (unsigned int)SIZE; ++i) {
        printf("%u", input[i]);
    }
    *numCombinations=*numCombinations+1;
    printf("\n");

} // end print combination

//~~~~~~~~~~~~~~~~~~~~~~SwitchaRoo~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

unsigned int SwitchaRoo(unsigned int value) {
    /*
    * PRE: takes in a value
    * POST: returns value related to it
    * PURPOSE: to swap values with its counterpart
    */
    switch(value) {
        case 1:return 2;                // represents button #1
        case 2:return 1;                // represents button #1
        case 3:return 4;                // represents button #2
        case 4:return 3;                // represents button #2
        case 5:return 6;                // represents button #3
        case 6:return 5;                // represents button #3
        case 7:return 8;                // represents button #4
        case 8:return 7;                // represents button #4
        case 9:return 0;                // represents button #5
        case 0:return 9;                // represents button #5
        default:return -1; // basically a try/catch - should never reach here
    } // end switch
} // end SwitchaRoo