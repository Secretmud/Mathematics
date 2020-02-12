#include <stdio.h>
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
        double x = atoi(argv[1]); 
        for (int i = 0; i < atoi(argv[2]); i++) {
            printf("%.64f\n", x);
            x = x - (f(x)/fd(x));
        }
    } else {
        printf("You've to pass two arguments, x and itterations");
    }
    return 0;
}

double f(double x) {
    return cos(x)-x;
}

double fd(double x) {
    return -sin(x)-1; 
}
