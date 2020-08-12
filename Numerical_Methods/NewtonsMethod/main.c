#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f(double x);
double fd(double x);

/*
 * Requires 2 parameters to run, 
 *      argument 1 - the x to check
 *      argument 2 - amount of itterations
 * */

int main(int argc, char * argv[]) {
    if (argc == 3) {
        double x = atof(argv[1]); 
        for (int i = 0; i < atoi(argv[2]); i++) {
            printf("%.10f\n", x);
            x = x - (f(x)/fd(x));
        }
    } else {
        printf("You've to pass two arguments, x and itterations\n");
    }
    return 0;
}

double f(double x) {
    return -0.2*(x-12)+0.005*100;
}

double fd(double x) {
    return -0.2*(x-12)+0.005*100;
}
