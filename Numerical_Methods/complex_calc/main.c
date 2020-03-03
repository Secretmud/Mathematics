#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define PI 3.1415926535897932384626433


double calc_imag(double number, double r);
double calc_real(double number, double r);
double calc_theta(double x, double y, int quadrant, double r);
int find_quadrant(double x, double y);

/* Creating a typedef for the complex number Z
 * */
typedef struct Complex {
    double power;
    double real;
    double imag;
    double theta;
    int quadrant;
    double r;
    char operator;
} Complex;

int main(int argc, char * argv[]) {
    // Initializing Complex as complex.
    Complex complex;
    // Checking if we have 4 arguments ./complex n a b. Where n is the power, a
    // is the real part and b is the imaginary part.
    if (argc == 4) {
        clock_t start = clock();
        // Using atoi to convert the commandline arguments into ints and
        // asigning them to the correct complex struct part.
        complex.power = atoi(argv[1]);
        complex.real = atoi(argv[2]);
        complex.imag = atoi(argv[3]);
        // Initializing a array with complex.power places. It's a VLA(variable
        // length array). The size is set in runtime.
        double numbers[(int)complex.power];
        // Finding the radius of of the cirlce. 
        complex.r = sqrt(pow(complex.real, 2)+pow(complex.imag, 2));
        // Finding out which quadrant the the original complex number is in.
        complex.quadrant = find_quadrant(complex.real, complex.imag);
        // Calculating the theta.
        complex.theta = calc_theta(complex.real, complex.imag, complex.quadrant, complex.r);
        printf("BEFORE CALCULATIONS \n \nREAL\t\t%.2f\nIMAG:\t\t%.2f\nQUADRANT:\t%d\nPOWER:\t\t%.2f\n\u03B8:\t\t%.2f\nRADIUS:\t\t%.2f\n", complex.real, complex.imag, complex.quadrant, complex.power, complex.theta, complex.r);
        // Calculating the new r with regards to the power.
        complex.r = pow(complex.r, 1/complex.power);
        printf("\nAFTER CALCULATIONS\n");
        printf("NEW RADIUS:\t%.6f\n", complex.r);
        // Calculating the new theta with regards to the power.
        complex.theta = complex.theta*1/complex.power;
        for (int i = 0; i < complex.power; i++) {
            numbers[i] = (complex.theta+i*(2*PI)/complex.power);
            complex.imag = calc_imag(numbers[i], complex.r);
            complex.real = calc_real(numbers[i], complex.r);
            printf("\nQUADRANT:\t%d\n", find_quadrant(complex.real, complex.imag));
            // Cleaning the output by adding a negative operator between the
            // real and imaginary part. If the imaginary part is negative.
            if (complex.imag < 0) {
                complex.operator = '-';
                complex.imag *= -1;
            } else {
                complex.operator = '+';
            }
            printf("%.6f%c%.6fi\n", complex.real, complex.operator, complex.imag);
        }
        printf("Total time:\t%.4fs\n", ((float)clock() - start)/CLOCKS_PER_SEC);
    } else {
        printf("You need to pass 3 arguments when running this program");
        printf("\n\t1: the nth power");
        printf("\n\t2: the real number");
        printf("\n\t3: the imaginary number\n\n");
    }
    return 0;
}
// Calculating the imaginary number using r and sin(theta)
double calc_imag(double number, double r) {
    return r*sin(number);
}
// Calculating the real number using r and cos(theta)
double calc_real(double number, double r) {
    return r*cos(number);
}
// Calculating theta, if the theta is negative then it will add PI, if not it
// will just @return the theta itself.
double calc_theta(double x, double y, int quadrant, double r) { 
    // Checking if numerator is set to 0
    if (y == 0) {
        double sin_theta = asin(y/r);
        double cos_theta = acos(x/r);
        int quad = find_quadrant(calc_real(sin_theta, r), calc_imag(sin_theta, r));
        printf("QUADRANT_O:\t%d\nQUADRANT_N:\t%d\nSIN:\t%.2f\nCOS:\t%.2f\n", quadrant, quad, sin_theta, cos_theta);
        if (quad == quadrant) {
            return sin_theta;
        } else {
            return cos_theta;
        }
    } else {
        if (atan(y/x) < 0) {
            return atan(y/x)+PI;
        } else {
            return atan(y/x);
        }
    }
}
// Finding the quadrant of x and y. 
int find_quadrant(double x, double y) {
    if (x >= 0 && y >= 0) return 1;
    if (x <= 0 && y >= 0) return 2;
    if (x <= 0 && y <= 0) return 3;
    if (x >= 0 && y <= 0) return 4;
}
