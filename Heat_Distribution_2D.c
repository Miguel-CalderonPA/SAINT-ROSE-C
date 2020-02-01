/*
 * Miguel Calderon
 * Date: 10/20/19
 * Last Modified 10/23/19
 * CSC 381 Professor O'Rourke
 */
#include <stdio.h>
#include <math.h> // for easier absolute value function called fabsf(float a)
#define MAX_ROW 10
#define MAX_COL 10
#define EPSILON .10     //testing
#define ITERATIONS 100  //testing
#define DIVISOR 4

//Prototypes
void printTable(float (*)[MAX_ROW]); // takes in 2D array by reference

int main() {

    //Variables
    //array variables
    float field1[MAX_COL][MAX_ROW]; // starting current field
    float field2[MAX_COL][MAX_ROW]; // starting next field
    float (*current)[MAX_ROW];      // 2D array pointer for current field
    float (*next)[MAX_ROW];         // 2D array pointer for next field
    float (*temp)[MAX_ROW];         // a temp to hold addresses during swap

    // Block Calculations
    float up,down,right,left;       // holds surrounding block values
    float avg;                      // holds average of surrounding blocks
    float sum;                      // hold sum of surrounding blocks (helper variable)
    float max;                      // holds max point of grid - highest difference

    //Termination Variables
    float epsilon;                  // holds convergence point
    int terminate;                  // holds max iterations given by user
    int count=0;                    // counts iterations

    //Coordinate Variables
    int xCoord, yCoord;             // holds row and column
    float nextCoords, currentCoords;  // used for epsilon math difference
    float coordDiff;                // difference between

    //Boundary Varaibles
    float topBound;
    float rightBound;
    float bottomBound;
    float leftBound;

    /*testing
    int stopper;
     */

    // assign pointers to respective arrays
    current=field1;
    next=field2;

    //User Input for error tolerance
    puts("Please Enter an Epsilon");
    scanf("%f", &epsilon);
    if(epsilon>(float).1) {                             //comparing floats wasn't ideal (future improvement)
        puts("invalid epsilon");
    }
    else {                                              // else means valid error tolerance
        puts("Please Enter the Max Number of Iterations");
        scanf("%d", &terminate);

        if(terminate>0) {                               // has to be positive

            //Enter in Boundaries
            puts("Please enter in TOP boundary value");
            scanf("%f", &topBound);
            puts("Please enter in RIGHT boundary value");
            scanf("%f", &rightBound);
            puts("Please enter in BOTTOM boundary value");
            scanf("%f", &bottomBound);
            puts("Please enter in LEFT boundary value");
            scanf("%f", &leftBound);
            //Final step – Add a prompt to enter the four boundary values in the order top, right
            //side, bottom and left side.



            //Fills Default Array
            for (int i = 0; i < MAX_COL; ++i) {         //traverse by columns
                for (int j = 0; j < MAX_ROW; ++j) {     //traverse by rows
                    if (i == 0) {
                        current[i][j] = leftBound;
                        next[i][j] = leftBound;
                    }// end filling  left wall
                    else if (i == MAX_COL-1) {
                        current[i][j] = rightBound;
                        next[i][j] = rightBound;
                    } // end filling right wall
                    else if (j==0) {
                        current[i][j] = topBound;
                        next[i][j] = topBound;
                    } // end filling ceiling
                    else if (j==MAX_ROW-1) {
                        current[i][j] = bottomBound;
                        next[i][j] = bottomBound;
                    } // end filling floor
                    else {
                        current[i][j] = 0;
                        next[i][j] = 0;
                    } // end filling middle of table

                } // end rows of array
            } // end columns of array

            printTable(current);
            // Computes Table Iterations
            while (terminate > count )                                  // has to be within given limit
            {
                for (xCoord = 1; xCoord <MAX_ROW-1 ; ++xCoord) {        // traverse by columns
                    for (yCoord = 1; yCoord < MAX_COL - 1; ++yCoord) {  // traverse by rows
                        up = current[yCoord][xCoord + 1];               // gets north value
                        down = current[yCoord][xCoord - 1];             // gets south value
                        right = current[yCoord + 1][xCoord];            // gets east value
                        left = current[yCoord - 1][xCoord];             // gets west value
                        sum = up + down + right + left;                 // adds all sides
                        avg = sum / (float) DIVISOR;                    // calculates average of sids
                        next[yCoord][xCoord] = avg;                     // puts it in next table
                      //  printTable(next); // testing/output for user
                    } // end rows
                } // end columns

                //Check if at error tolerance
                xCoord=1;
                yCoord=1;
                nextCoords = next[xCoord][yCoord];                      // grabs initial value from next(readability)
                currentCoords = current[xCoord][yCoord];                // grabs initial value from current(readability)
                coordDiff = nextCoords-currentCoords;                   // holds difference between coords(readability)1
                max = fabsf(coordDiff);                // subtracts . absolute value and puts into max

                for (xCoord = 1; xCoord <MAX_ROW-1 ; ++xCoord) {        // traverse rows
                    for (yCoord = 1; yCoord < MAX_COL - 1; ++yCoord) {  // traverse columns
                        nextCoords = next[xCoord][yCoord];              // grabs next set of coords from next
                        currentCoords = current[xCoord][yCoord];        // grabs next set of coords from current
                        coordDiff =nextCoords - currentCoords;         // holds next difference
                        if(fabsf(coordDiff)>max) {                        // determines if max needs replacement
                            max = fabsf(coordDiff);                 // replaces max if needed
                        } // end check max
                    } // end columns
                } // end rows

                /*testing
                printf("Iterations="%d", count);
                puts("\n\nthis is current before switch");
                printTable(current);
                puts("\n\nThis is next before switch");
                printTable(next);
                */

                //Swap tables using pointers
                temp = current;
                current = next;
                next = temp;

                /* testing
                puts("\n\nthis is current after switch");
                printTable(current);
                puts("\n\nThis is next after after switch");
                printTable(next);
                */

                count++; // counts iterations

                if(max<=epsilon) {       // checks error tolerance if true termination gets count thus ending iteration
                    terminate=count;

                } // end if max is epsilon
                //  int stopper = getchar(); // testing
            } // end while

            printTable(current);

            if(max<=epsilon) {                               // if loop ended due to epsilon
                puts("\nConverged.");
                printf("Iterations=%d\n", count);
           //    printf("Max=%4.5f\n", max); // testing
            } // end if convergence
            else {                                          // if loop ended due to max iterations
                puts("\nFailed to Converge");
                printf("Iterations=%d\n", count);
             //   printf("Max=%4.5f\n", max); //testing
            } // end if max iterations
        }// end if invalid iterations from user input
        else {
            if (terminate == 0) {
                puts("Oh WOW! 0 iterations cool, awesome, let me just do absolutely no work for you...");
            } else {
                puts("Iterations must be positive!");
            }
        } // end else
    } // end if invalid epsilon from user input
    return 0;
} // end main


void printTable(float array[][MAX_ROW] ) {                  // float array is reference
    /*
     * PRE: Takes in a 2D Array pointer
     * POST:   2D Array is displayed on screen
     * PURPOSE: Takes in a 2D array and visually depicts how array is storing data
     */
    //Cosmetics
    printf("\n| Col # | Col 1 | Col 2 | Col 3 | Col 4 | Col 5 | Col 6 | Col 7 | Col 8 | Col 9 | Col10 |");
    printf("\n-----------------------------------------------------------------------------------------");

    for (int i = 0; i < MAX_COL; ++i) {                     // traverse columns
        printf("\n Row %d: |", i);
        for (int j = 0; j < MAX_ROW; ++j) {                  // traverse rows
            printf(" %4.2f |", array[i][j]);
        } // end inside for
    }// end outside for
} // end printTable