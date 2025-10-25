/* Implementation of a basic calculator with the following operations:
-> Addition
-> Subtraction
-> Multiplication
-> Division
-> Square root
-> Power
-> Trigonometrics ([sin, cos, tan])

(version 1.0)
Last revision: 16th April 2025

* Copyright © 2025 Lourenço Afonso Moiane Júnior
* All rights reserved ®  */

#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <float.h>
#include <pthread.h>
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>

// Function declarations for operations
double add(double num1, double num2);
double subtract(double num1, double num2);
double multiply(double num1, double num2);
double divide(double num1, double num2);
void *square_root(void * pi);
double power(double num1, double num2);
double trig();

// Function declarations for history
void write_to_history(const char *output);
void see_history();
void clear_history();

#endif
