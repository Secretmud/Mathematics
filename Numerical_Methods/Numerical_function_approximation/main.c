#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <omp.h>
#include <time.h>

typedef struct Approx {
    const char * name;
    double step_size;
    double current_step;
    double init_val;
    double scope[2];
    double scope_len;
    int step_length;
    int col;
    int row;
    int last_index;
} Approx;

void calc_matrix(Approx *a, double **matrix);
double g_x(double x);
double a_x(double x);
void print_help();
void rref(int row, int col, double **array, int print_steps);
void pMatrix(int row, int col, double **array);
void file_create(Approx *a, double **matrix);

int main(int argc, char *argv[]) {
    Approx *approx = malloc(sizeof(Approx));
    if (argc >= 2) {
        if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
            print_help();
            return 0;
        }
        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "-l") == 0)
                approx->step_length = atoi(argv[i + 1]);
            if (strcmp(argv[i], "-s") == 0) {
                approx->scope[0] = atof(argv[i + 1]);
                approx->scope[1] = atof(argv[i + 2]);
            }
            if (strcmp(argv[i], "-i") == 0)
                approx->init_val = atof(argv[i + 1]);
            if (strcmp(argv[i], "-n") == 0)
                approx->name = argv[i + 1];
        }

        approx->scope_len = abs(approx->scope[0] - approx->scope[1]);
        printf("SCOPE_LEN:\t%f\n", approx->scope_len);
        approx->step_size = approx->scope_len/((double)approx->step_length - 1);
        approx->row = approx->step_length - 1;
        approx->col = approx->step_length;
        double ** matrix;
        clock_t calc_matrix_time, rref_time, file_create_time;
        matrix = calloc(approx->row, sizeof(double *));
        for (int i = 0; i < approx->row; i++)
            matrix[i] = calloc(approx->col, sizeof(double));

        #pragma omp parallel
        {
            #pragma omp for
            for (int i = 0; i < approx->row; i++) {
                for (int x = 0; x < approx->col; x++) {
                    matrix[i][x] = 0.0;
                }
            }
        }
        approx->last_index = approx->col - 1;
        approx->current_step = approx->step_size;
        calc_matrix_time = clock();
        calc_matrix(approx, matrix);
        printf("Calc matrix time:\t%.4fs\n", ((double)clock() - calc_matrix_time)/CLOCKS_PER_SEC);
        rref_time = clock();
        rref(approx->row, approx->col, matrix, 0);
        printf("Row reduced echelon form time:\t%.4fs\n", ((double)clock() - rref_time)/CLOCKS_PER_SEC);
        file_create_time = clock();
        file_create(approx, matrix);
        printf("File create time:\t%.4fs\n", ((double)clock() - file_create_time)/CLOCKS_PER_SEC);
        free(matrix);
        free(approx);
    } else {
        printf("You've to supply a argument. -h/--help for more info\n\n");
    }
    return 0;
}

double g_x(double x) {
    return (cos(x)-sin(x))/(1+x*x);
}
double a_x(double x) {
    return exp(x-sin(x))+2*x;
}


void calc_matrix(Approx *a, double **matrix) {
    const char * info = "STEP_SIZE:%f\nSTEP_LENGTH:%d\nLAST_INDEX:%d\nINIT_VAL:%f\n";
    printf(info, a->step_size, a->step_length, a->last_index, a->init_val);
    double step;
    #pragma omp parallel
    {
        #pragma omp for
        for (int i = 0; i < a->row; i++) {
            step = (i+1)*a->step_size+a->scope[0];
            if (i + 1 == a->row) {
                matrix[i][i - 2] = 1;
                matrix[i][i - 1] = -4;
                matrix[i][i] = 3 + a_x(step);
                matrix[i][a->last_index] = g_x(step);
            }
            if (i == 0) {
                matrix[i][i] = a_x(step);
                matrix[i][i + 1] = 1;
                matrix[i][a->last_index] = a->init_val + g_x(step);
            }
            if (i > 0 && i + 1 < a->row) {
                matrix[i][i - 1] = -1;
                matrix[i][i] = a_x(a->current_step);
                matrix[i][i + 1] = 1;
                matrix[i][a->last_index] = g_x(step);
            }
        }
    }
    
}

void print_help() {
    printf("to use the program supply:\n\t-l=LENGTH\n\t-s=SCOPE\n\t-i=INIT_VALUE\n\t-n=FILENAME\n");
}

void file_create(Approx *a, double **matrix) {
    FILE *f;
    f = fopen(a->name, "wb");
    a->current_step = a->step_size;
    for (int i = 0; i < a->row; i++) {
        fprintf(f, "%f %f", a->current_step+a->scope[0], matrix[i][a->last_index]);
        fputs("\n", f);
        a->current_step += a->step_size;
    }
    fclose(f);
}

void pMatrix(int row, int col, double **array)
{
    for (int i=0; i<row; i++) {
        for (int j=0; j<col; j++) {
            printf("%.2f\t", array[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}

void rref(int row, int col, double **array, int print_steps) {
    int lead = 0, i = 0;
    double hold[col];
    printf("Loading : ");
    for (int r = 0; r < row; r++) {
        if (col <= lead) {
            break;
        }
        i = r;
        while (array[i][lead] == 0) {
            i++;
            if (row == i) {
                i = r;
                lead++;
                if (col == lead) {
                    break;
                }
            }
        }
        for (int j = 0; j < col; j++) {
            hold[j] = array[i][j];
            array[i][j] = array[r][j];
            array[r][j] = hold[j];
        }
        if (array[r][lead] != 0) {
            double divisor = array[r][lead];
            for (int i = 0; i < col; i++) {
                if (array[r][i] != 0.0)
                    array[r][i] /= divisor;
            }
        }
        for (i = 0; i < row; i++) {
            if (i != r) {
                double base = array[i][lead];
                for (int k = 0; k < col; k++) {
                    if (array[i][k] != 0.0)
                        array[i][k] -= base*array[r][k];
                }
            }
        }
        if (r%print_steps==0)
            printf("\u0291");
        lead++;
    }
    printf("\n");
}
