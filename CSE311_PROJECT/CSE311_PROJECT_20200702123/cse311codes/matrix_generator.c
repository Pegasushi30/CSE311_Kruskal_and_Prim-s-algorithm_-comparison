#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int agrc, char **argv) {
    if (agrc != 3) {
        printf("This program requires 2 int arguments. First one represents the number of vertices second represent edge generation chance.\n");
        return EXIT_FAILURE;
    }

    int verticeCount;
    if (sscanf(argv[1], "%d", &verticeCount) != 1) {
        printf("Invalid command line argument for the first argument. Please enter a valid int.\n");
        return EXIT_FAILURE;
    }

    if (verticeCount <= 0) {
        printf("Please enter a postive int number (greater than zero).\n");
        return EXIT_FAILURE;
    }

    int edgeChance;
    if (sscanf(argv[2], "%d", &edgeChance) != 1) {
        printf("Invalid command line argument for the second argument. Please enter a valid int.\n");
        return EXIT_FAILURE;
    }

    if (edgeChance < 0 || edgeChance > 100) {
        printf("Invalid command line argument for the second argument. Please enter a int value between 0 and 100.\n");
        return EXIT_FAILURE;
    }

    srand(time(NULL));
    int currentRandomNumber = 0;

    int **array;

    array = (int **)malloc(verticeCount * sizeof(int *));
    if (array == NULL) {
        printf("Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < verticeCount; i++) {
        array[i] = (int *)malloc(verticeCount * sizeof(int));
        if (array[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(array[j]);
            }
            free(array);
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < verticeCount; i++) {
        for (int j = 0; j < verticeCount; j++) {
            array[i][j] = 0;
        }
    }

    for (int i = 0; i < verticeCount; i++) {
        for (int j = 0; j < verticeCount; j++) {
            if (i == j) {
                array[i][j] = 0;
                array[j][i] = 0;
            } else if (i + 1 != verticeCount && j == i + 1) {
                currentRandomNumber = (rand() % 9) + 1;
                array[i][j] = currentRandomNumber;
                array[j][i] = currentRandomNumber;
            } else if (array[i][j] == 0) {
                currentRandomNumber = (rand() % 100) + 1;
                if (currentRandomNumber <= edgeChance) {
                    currentRandomNumber = (rand() % 9) + 1;
                } else {
                    currentRandomNumber = 0;
                }
                array[i][j] = currentRandomNumber;
                array[j][i] = currentRandomNumber;
            }
        }
    }

    FILE *matrixOutput = fopen("matrix_output.txt", "w");

    if (matrixOutput == NULL) {
        printf("Cannot write to \"matrix_output.txt\", exiting...");
        for (int i = 0; i < verticeCount; i++) {
            free(array[i]);
        }

        free(array);
        return EXIT_FAILURE;
    }

    fprintf(matrixOutput, "%d\n", verticeCount);

    for (int i = 0; i < verticeCount; i++) {
        for (int j = 0; j < verticeCount; j++) {
            fprintf(matrixOutput, "%d\t", array[i][j]);
        }
        fprintf(matrixOutput, "\n");
    }

    fclose(matrixOutput);

    for (int i = 0; i < verticeCount; i++) {
        free(array[i]);
    }

    free(array);

    return EXIT_SUCCESS;
}