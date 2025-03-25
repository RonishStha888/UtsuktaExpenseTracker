#include <stdio.h>
#include <stdlib.h>

void read_dataset(int x[], int y[], int *size, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file: %s\n", filename);
        exit(1);
    }

    while (fscanf(file, "%d,%d", &x[*size], &y[*size]) == 2) {
        (*size)++;
    }
    fclose(file);
}

void linear_regression(int x[], int y[], int size, double *b, double *a) {
    double sum_x = 0, sum_y = 0, sum_xy = 0, sum_x2 = 0;
    for (int i = 0; i < size; i++) {
        sum_x += x[i];
        sum_y += y[i];
        sum_xy += x[i] * y[i];
        sum_x2 += x[i] * x[i];
    }

    *b = ((size * sum_xy) - (sum_x * sum_y)) / (size * sum_x2 - sum_x * sum_x);
    *a = ((sum_y * sum_x2) - (sum_x * sum_xy)) / (size * sum_x2 - sum_x * sum_x);
}

int main() {
    int x[500], y[500], size = 0;

    read_dataset(x, y, &size, "datasetLR1.txt");
    read_dataset(x, y, &size, "datasetLR2.txt");
    read_dataset(x, y, &size, "datasetLR3.txt");
    read_dataset(x, y, &size, "datasetLR4.txt");

    double b, a;
    linear_regression(x, y, size, &b, &a);

    printf("Equation: y = %.2fx + %.2f\n", b, a);

    double input_x, output_y;
    printf("Enter a value for x: ");
    scanf("%lf", &input_x);

    output_y = b * input_x + a;
    printf("For x = %.2f, predicted y = %.2f\n", input_x, output_y);

    return 0;
}
