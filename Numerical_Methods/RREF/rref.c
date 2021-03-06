#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Written with inspiration from the book "Praktisk Introduksjon til Numberiske
 * Metodar", written by Solve Selsto. 
 * @author Tor Kristian Dahle
 * @date 17-01-2020
 * @subject Matte1000 DAFE1000
 * */

void rref(int row, int col, double array[][col], int print_steps);
void pMatrix(int row, int col, double array[][col]); // Outputs the matrix
/*
 * How to compile with gcc:
 *      gcc -o rref main.c
 *          where -o let's you set the output file name
 * This program uses 3 arguments to run as of right now.
 * If you compile it like stated above, run it like this on linux.
 *      ./rref FILE ROWS COLS
 * To make the program actually usable I've decided to take in the file itself
 * as a running argument.
 * */
int main(int argc, char * argv[]) {
    FILE *f;
    int row = atoi(argv[2]), col = atoi(argv[3]), print_steps = 0;
    double array[row][col];
    f = fopen(argv[1], "r");
    for (int i = 0; i < argc; i++)
        if (strcmp(argv[i], "-p") == 0)
            print_steps = 1;
    // argv[0] is the file executed, if the total amout of arguments is 1 then
    // the program will exit with a description on how to run it.
    if (argc >= 4) {
        printf("FILE:\t%s\nROWS:\t%s\nCOLS:\t%s\nARGUMENTS:\t%d\nPRINT_STEPS:\t%d\n\n", argv[1], argv[2], argv[3], argc, print_steps);
        if (f) {
            // puts the contents of the file into a 2d-array
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < col; j++) {
                    fscanf(f, "%lf", &array[i][j]);
                }
            }
            // closing the file stream, so that other programs can use the file. 
            fclose(f);
        }
        // pMatrix - print matrix before rref is performed
        pMatrix(row, col, array);
        // Reduced row echelon form
        rref(row, col, array, print_steps);
        // pMatrix - printing the matrix after rref is performed
        printf("\n");
        pMatrix(row, col, array);
    } else {
        printf("You need to supply 3 arguments:\n\ta.out file rows col\n\n");
        fclose(f);
    }
    return 0;
}

/* Prints the matrix, using a nested for-loop. taking row, col and array as
 * parameters.
 * */
void pMatrix(int row, int col, double array[][col])
{
    for (int i=0; i<row; i++) {
        for (int j=0; j<col; j++) {
            printf("%.2f\t", array[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}

/* Reduced Row Echcelon Form:
 * Used wikipedia and other online resources to work out the algorithm
 * 1) Every row has a leading 1
 *      a) A given row has to have a leading 1 to the right of the row above
 * 2) Rows consisting of just zero's are placed at the bottom
 * 3) If a matrix has a leading 1 at the top right corner then every row below
 *    consists of only zeroes
 * */
void rref(int row, int col, double array[][col], int print_steps) {
    int lead = 0, i = 0;
    //create a pointer array, size of col. Used for swapping rows.
    double hold[col];
    for (int r = 0; r < row; r++) {
        // checks if the col is less or equal to 0, which would mean that the
        // matrix it self is non exsistent.
        if (col <= lead) {
            return;
        }
        i = r;
        // checks if the leading number is 0. if i hits row, which would be out
        // of scope it sets i to be r(the value of the initial for-loop.
        // adds 1 to lead and returns if lead is equal to col which also would
        // be out of scope of the array
        while (array[i][lead] == 0) {
            i++;
            if (row == i) {
                i = r;
                lead++;
                if (col == lead) {
                    return;
                }
            }
        }
        //swap row i and row r
        for (int j = 0; j < col; j++) {
            hold[j] = array[i][j];
            array[i][j] = array[r][j];
            array[r][j] = hold[j];
        }
        //If array[r][lead] doesn't qeual 0, divide row r by array[r][lead]
        if (array[r][lead] != 0) {
            double divisor = array[r][lead];
            if (print_steps == 1)
                printf("\nROW -> %d\tDIVISOR -> %.6f\t ROW[%d]/DIVISOR  -> %d\n", i, divisor, r, r);
            for (int i = 0; i < col; i++)
                if (print_steps == 1)
                    printf("%.2f\t", array[r][i]);
            if (print_steps == 1)
                printf("\n");
            for (int i = 0; i < col; i++) {
                array[r][i] /= divisor;
                if (print_steps == 1)
                    printf("%.2f\t", array[r][i]);
            }
            if (print_steps == 1)
                printf("\n");
        }
        for (i = 0; i < row; i++) {
           //Subtract array[i][lead] multiplied by row r from row i
            if (i != r) {
                double base = array[i][lead];
                if (print_steps == 1)
                    printf("\nROW -> %d\tBASE -> %.6f\tBASE*ROW[%d] - ROW[%d] -> %d\n", i, base, i, r,  r);
                for (int k = 0; k < col; k++)
                    if (print_steps == 1)
                        printf("%.2f\t", array[i][k]);
                if (print_steps == 1)
                    printf("\n");
                for (int k = 0; k < col; k++) {
                    array[i][k] -= base*array[r][k];
                    if (print_steps == 1)
                        printf("%.2f\t", array[i][k]);
                }
                if (print_steps == 1)
                    printf("\n");
            }
        }
        lead++;
    }
}
