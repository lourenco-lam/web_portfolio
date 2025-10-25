/* Implementation of a basic calculator with the following operations:
-> Addition
-> Subtraction
-> Multiplication
-> Division
-> Square root
-> Power
-> Trigonometrics ([sin, cos, tan, cot, sec, cosec])

(version 2.0)
Last revision: 16th April 2025

Update summary: Addition of new trigonometric functions [cotagent, secant & cosecant]

* Copyright © 2025 Lourenço Afonso Moiane Júnior
* All rights reserved ®  */

#include "calculator.h"

// Global variables
double num1, num2, result;
// trig() variables
char buf[10];
double arg = 0;
char function[4];
// Main variables
double result;
char buffer[20];
char operation[20];
char output[100];
pthread_t t;

// Functions for all operations
double add(double num1, double num2) {
    return num1 + num2;
}

double subtract(double num1, double num2) {
    return num1 - num2;
}

double multiply(double num1, double num2) {
    return num1 * num2;
}

double divide(double num1, double num2) {
    if (num2 == 0) {
        printf("Error: Division by zero!\n");
        return -1;
    }
    return num1 / num2;
}

void *square_root(void * pi) {
    result = sqrt(num1);
    if (isnan(result)) {
        snprintf(output, sizeof(output), "\nResult of square_root: sqrt(%g) [Math ERROR]\n\n", num1);
        printf("%s", output);
        write_to_history(output);
    } else {
        snprintf(output, sizeof(output), "Result of square_root: sqrt(%g) = %g\n\n", num1, result);
        printf("%s", output);
        write_to_history(output);
    }
    return 0;
}
double power(double num1, double num2) {
    result = pow(num1, num2);
    return result;
}

// Specific for (cos, sec & cosec) trig functions
double cot(double x) {
    double t = tan(x);
    if (fabs(t) < DBL_EPSILON) {  // tan(x) ≈ 0 → undefined
        printf("\nMath Error: cot(%.2f°) is undefined (tan(x) = 0)\n\n", x * 180.0 / M_PI);
        return NAN;
    }
    return 1.0 / t;
}

double sec(double x) {
    double c = cos(x);
    if (fabs(c) < DBL_EPSILON) {  // cos(x) ≈ 0 → undefined
        printf("\nMath Error: sec(%.2f°) is undefined (cos(x) = 0)\n\n", x * 180.0 / M_PI);
        return NAN;
    }
    return 1.0 / c;
}

double cosec(double x) {
    double s = sin(x);
    if (fabs(s) < DBL_EPSILON) {  // sin(x) ≈ 0 → undefined
        printf("\nMath Error: cosec(%.2f°) is undefined (sin(x) = 0)\n\n", x * 180.0 / M_PI);
        return NAN;
    }
    return 1.0 / s;
}

double trig() {

    while (1) {
        // Enter desired trigonometric function
        printf("\nAvialable functions:\n-sin(x)\n-cos(x)\n-tan(x)\n-cot(x)\n-sec(x)\n-cosec(x)\n");
		printf("\nSelect a function -> ");
        memset(buf, 0, sizeof(buf));
        if (fgets(buf, sizeof(buf), stdin) != NULL) {
            if (strcmp(buf, "exit\n") == 0) {
                printf("Exited calculator!\n");
                exit(0);
            }

            // Store function name in 'function' variable and check validity
            sscanf(buf, "%s", function);  // Extract function name
			if (strcmp(function, "sin") && strcmp(function, "cos") && strcmp(function, "tan") &&
			strcmp(function, "cot") && strcmp(function, "sec") && strcmp(function, "cosec"))
			{
				printf("Invalid function!\n\n");
                continue;
            }

            // Enter argument for trigonometric function
            printf("\nEnter the argument (degrees): ");
            memset(buf, 0, sizeof(buf));
            if (fgets(buf, sizeof(buf), stdin) != NULL) {
                if (strcmp(buf, "exit\n") == 0) {
                    printf("Exited calculator!\n");
                    exit(0);
                }

                if (sscanf(buf, "%lf", &arg) != 1) {
                    printf("Invalid input! Enter a number for the argument...\n\n");
                    continue;
                }
            }

            // Convert to degrees
            num1 = arg * M_PI / 180.0;

            // Compute result based on function
            if (strcmp(function, "sin") == 0) {
                result = sin(num1);
                snprintf(output, sizeof(output), "\nResult: sin(%g) = %g\n", arg, result);
            }
            else if (strcmp(function, "cos") == 0) {
                result = cos(num1);
                snprintf(output, sizeof(output), "\nResult: cos(%g) = %g\n", arg, result);
            }
            else if (strcmp(function, "tan") == 0) {
                result = tan(num1);
                snprintf(output, sizeof(output), "\nResult: tan(%g) = %g\n", arg, result);
            }
			else if (strcmp(function, "cot") == 0) {
				result = cot(num1);
				if (isnan(result)) break;
				snprintf(output, sizeof(output), "\nResult: cot(%g) = %g\n", arg, result);
			}
			else if (strcmp(function, "sec") == 0) {
				result = sec(num1);
				if (isnan(result)) break;
				snprintf(output, sizeof(output), "\nResult: sec(%g) = %g\n", arg, result);
			}
			else if (strcmp(function, "cosec") == 0) {
				result = cosec(num1);
				if (isnan(result)) break;
				snprintf(output, sizeof(output), "\nResult: cosec(%g) = %g\n", arg, result);
			}
            printf("%s\n", output);
            write_to_history(output);
			break;
        }
    }
	return result;
}

void write_to_history(const char *output) {
    FILE *file = fopen("history.txt", "a"); // Open file in append mode
    if (file == NULL) {
        perror("Error opening file for writing!\n");
        exit(1);
    }

    fprintf(file, "%s", output); // Write the entire output string to the file
    fclose(file);
}

void see_history() {
    FILE *file = fopen("history.txt", "r");
    if (file == NULL) {
        perror("Error opening file for reading!\n");
        exit(1);
    }
    
    char line[2048];
    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
    }
    fclose(file);
}


void clear_history() {
    FILE *file = fopen("history.txt", "r"); // Open in read mode first to check size
    if (file == NULL) {
        printf("Error opening file to check history!\n");
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fclose(file);

    if (size == 0) {
        printf("\nHistory already cleared!\n\n");
        return;
    }

    // Now actually clear the file
    file = fopen("history.txt", "w"); // Truncate file
    if (file == NULL) {
        printf("Error opening file to clear history!\n");
        exit(1);
    }

    fclose(file);
    printf("\nHistory cleared successfully!\n\n");
}