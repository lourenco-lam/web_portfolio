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

#include "calculator.h"

double num1 = 0, num2 = 0, result = 0;

int main() {
    double result;
    char buffer[20];
    char output[100];
    pthread_t t;
    char *input;

    // Initialize readline history
    using_history();
    stifle_history(100); // Limit history to 100 entries

    printf("To see all operations available type [sos].\n");
    printf("Type [history] to see calculator history.\n");
    printf("Type [exit] to terminate calculator.\n\n");

    while(1) {

        char *input = readline("Enter operation or command: ");

        // Add non-empty input to history
        if (*input) {
            add_history(input);
        }

        // Display available operations
        if (strcmp(input, "sos") == 0) {
            printf("\nAvailable operations:\n");
            printf("\n-> add (a)\n-> subtract (s)\n-> multiply (m)\n-> divide (d)\n-> square_root (sqrt)\n-> power (p)\n-> trigonometrics (trig)\n\n");
            free(input);
            continue;
        }

        // Skip empty input
        if (strcmp(input, "") == 0) {
            free(input);
            continue;
        }

        // Exit command
        if (strcmp(input, "exit") == 0) {
            printf("\nExited calculator!\n");
            free(input);
            exit(0);
        }

        // Display calculator history
        if (strcmp(input, "history") == 0) {
            printf("\n[Calculator History]\n\n");
            see_history();
            free(input);
            continue;
        }

        // History command
        if (strcmp(input, "command history") == 0) {
            printf("\n[Command History]\n\n");
            
            // macOS compatible implementation
            HISTORY_STATE *hist_state = history_get_history_state();
            if (hist_state) {
                for (int i = 0; i < hist_state->length; i++) {
                    HIST_ENTRY *entry = history_get(i + history_base);
                    if (entry) {
                        printf("%d: %s\n", i + history_base, entry->line);
                    }
                }
                free(hist_state);
            }
            printf("\n");
            free(input);
            continue;
        }

        // Clear history command
        if (strcmp(input, "clear history") == 0) {
            clear_history();
            free(input);
            continue;
        }

        // calculate square_root
        if (strcmp(input, "sqrt") == 0) {
            while (1) {
                // Enter number to calculate square_root
                printf("\nEnter number: ");
                if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
                    if (strcmp(buffer, "exit\n") == 0) {
                        printf("Exited calculator!\n");
                        exit(0);
                    }
                    if (sscanf(buffer, "%lf", &num1) != 1) {
                        printf("Invalid input! Enter a number...\n\n");
                        continue;
                    }
                }
                free(input);
                break;
            }

            if (pthread_create(&t, NULL, square_root, NULL) != 0) {
                printf("Error calculating square_root!");
                exit(-1);
            }
            pthread_join(t, NULL);
            continue;
        }

        // Calculate power (num1^num2)
        if (strcmp(input, "p") == 0) {

            while (1) {
                // Enter base
                printf("\nEnter base number: ");
                if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
                    if (strcmp(buffer, "exit\n") == 0) {
                        printf("Exited calculator!\n");
                        exit(0);
                    }
                    if (sscanf(buffer, "%lf", &num1) != 1) {
                        printf("Invalid input! Enter a number...\n\n");
                        continue;
                    }
                }
                printf("\n");

                // Enter exponent
                printf("Enter exponent number: ");
                if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
                    if (strcmp(buffer, "exit\n") == 0) {
                        printf("Exited calculator!\n");
                        exit(0);
                    }
                    if (sscanf(buffer, "%lf", &num2) != 1) {
                        printf("Invalid input! Enter a number...\n\n");
                        continue;
                    }
                }
                break;
            }
            printf("\n");
            result = power(num1, num2);
            snprintf(output, sizeof(output), "Result of power: %g^%g = %g\n\n", num1, num2, result);
            printf("%s", output);
            write_to_history(output);
            free(input);
            continue;
        }

        // calculate trigonometric (sin, cos or tan)
        if (strcmp(input, "trig") == 0) {
            result = trig();
            free(input);
        }

        // Check for valid entered operation (a, s, m, d or p)
        else if (!(strcmp(input, "a") == 0 || strcmp(input, "s") == 0 ||
                  strcmp(input, "m") == 0 || strcmp(input, "d") == 0)) {

            printf("Invalid operation/command!\n \n");
            free(input);
            continue;
        }

        else {
            while (1) {
                // Enter first number
                printf("\nEnter first number: ");
                if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
                    if (strcmp(buffer, "exit\n") == 0) {
                        printf("Exited calculator!\n");
                        exit(0);
                    }
                    if (sscanf(buffer, "%lf", &num1) != 1) {
                        printf("Invalid input! Enter a number...\n\n");
                        continue;
                    }
                }
                printf("\n");

                // Enter second number
                printf("Enter second number: ");
                if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
                    if (strcmp(buffer, "exit\n") == 0) {
                        printf("Exited calculator!\n");
                        exit(0);
                    }
                    if (sscanf(buffer, "%lf", &num2) != 1) {
                        printf("Invalid input! Enter a number...\n\n");
                        continue;
                    }
                }
                printf("\n");
                break;
            }

            // Execution of operations (a, s, m, or d)
            if (strcmp(input, "a") == 0) {
                if (num2 < 0) {
                    result = subtract(num1, -num2);
                    snprintf(output, sizeof(output), "Result of addition: %g + (-%g) = %g\n\n", num1, -num2, result);
                    printf("%s", output);
                    write_to_history(output);
                } else {
                    result = add(num1, num2);
                    snprintf(output, sizeof(output), "Result of addition: %g + %g = %g\n\n", num1, num2, result);
                    printf("%s", output);
                    write_to_history(output);
                }
            }
            else if (strcmp(input, "s") == 0) {
                if (num2 < 0) {
                    result = add(num1, -num2);
                    snprintf(output, sizeof(output), "Result of subtraction: %g - (-%g) = %g\n\n", num1, -num2, result);
                    printf("%s", output);
                    write_to_history(output);
                } else {
                    result = subtract(num1, num2);
                    snprintf(output, sizeof(output), "Result of subtraction: %g - %g = %g\n\n", num1, num2, result);
                    printf("%s", output);
                    write_to_history(output);
                }
            }
            else if (strcmp(input, "m") == 0) {
                if (num2 < 0) {
                    result = multiply(num1, -num2);
                    snprintf(output, sizeof(output), "Result of multiplication: %g * (-%g) = %g\n\n", num1, -num2, result);
                    printf("%s", output);
                    write_to_history(output);
                } else {
                    result = multiply(num1, num2);
                    snprintf(output, sizeof(output), "Result of multiplication: %g * %g = %g\n\n", num1, num2, result);
                    printf("%s", output);
                    write_to_history(output);
                }
            }
            else if (strcmp(input, "d") == 0) {
                result = divide(num1, num2);
                snprintf(output, sizeof(output), "Result of division: %g / %g = %g\n\n", num1, num2, result);
                printf("%s", output);
                write_to_history(output);
            }
        }
    }
    free(input);
    return EXIT_SUCCESS;
}