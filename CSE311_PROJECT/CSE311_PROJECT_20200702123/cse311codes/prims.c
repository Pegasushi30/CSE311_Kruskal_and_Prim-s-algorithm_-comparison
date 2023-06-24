#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

typedef struct Edge {
    int u;
    int v;
    int weight;
} Edge;

int findMinKey(int key[], int mstSet[], int n)
{
    int min = INT_MAX;
    int minIndex = -1;

    for (int v = 0; v < n; v++) {
        if (mstSet[v] == 0 && key[v] < min) {
            min = key[v];
            minIndex = v;
        }
    }
    return minIndex;
}

void primAlgo(int n, int** graph, int* minCost, Edge* edges)
{
    int* parent = malloc(n * sizeof(int));
    int* key = malloc(n * sizeof(int));
    int* mstSet = malloc(n * sizeof(int));
    //Edge* edges = malloc((n - 1) * sizeof(Edge));

    for (int i = 0; i < n; i++) {
        key[i] = INT_MAX;
        mstSet[i] = 0;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < n - 1; count++) {
        int u = findMinKey(key, mstSet, n);

        mstSet[u] = 1;

        for (int v = 0; v < n; v++) {
            if (graph[u][v] && mstSet[v] == 0 && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    for (int i = 1; i < n; i++) {
        edges[i - 1].u = parent[i];
        edges[i - 1].v = i;
        edges[i - 1].weight = graph[i][parent[i]];
        *minCost += graph[i][parent[i]];
    }

    free(parent);
    free(key);
    free(mstSet);
}


int main(int argc, char* argv[])
{
    if (argc != 2) {
        printf("Usage: ./program <input_file>\n");
        return 1;
    }

    FILE* inputFile = fopen(argv[1], "r");
    if (inputFile == NULL) {
        printf("Failed to open the input file.\n");
        return 1;
    }

    int n;
    if (fscanf(inputFile, "%d", &n) != 1) {
        printf("Failed to read the number of vertices.\n");
        fclose(inputFile);
        return 1;
    }

    int** graph = malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++)
        graph[i] = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (fscanf(inputFile, "%d", &graph[i][j]) != 1) {
                printf("Failed to read the weights of the edges.\n");
                for (int k = 0; k <= i; k++)
                    free(graph[k]);
                free(graph);
                fclose(inputFile);
                return 1;
            }
        }
    }

    fclose(inputFile);

    int minCost = 0;

    clock_t start, end;
    double execution_time;
    double execution_time1;
    double execution_time2;
    double execution_time3;
    double execution_time4;
    Edge* edges;
    edges = malloc((n - 1) * sizeof(Edge));

    start = clock();
    primAlgo(n, graph, &minCost, edges);
    end = clock();

    execution_time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;
    printf("1st run (discarded) %lf ms\n", execution_time);

    start = clock();
    primAlgo(n, graph, &minCost, edges);
    end = clock();
    minCost = 0;

    execution_time1 = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;
    printf("2nd run: %lf ms\n", execution_time1);

    start = clock();
    primAlgo(n, graph, &minCost, edges);
    end = clock();
    minCost = 0;

    execution_time2 = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;
    printf("3rd run: %lf ms\n", execution_time2);

    start = clock();
    primAlgo(n, graph, &minCost, edges);
    end = clock();
    minCost = 0;

    execution_time3 = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;
    printf("4th run: %lf ms\n", execution_time3);

    start = clock();
    primAlgo(n, graph, &minCost, edges);
    end = clock();

    execution_time4 = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;
    printf("5th run: %lf ms\n", execution_time4);

    double average=(execution_time1+execution_time2+execution_time3+execution_time4)/4;
    printf("Average runtime is %lf ms\n",average);

  /*  
    printf("Following are the edges in the constructed MST:\n");
    for (int i = 0; i < n - 1; i++)
        printf("%d -- %d == %d\n", edges[i].u, edges[i].v, edges[i].weight);
    printf("Minimum Cost Spanning Tree: %d\n", minCost);
    */

    free(edges);

    for (int i = 0; i < n; i++)
        free(graph[i]);
    free(graph);

    return 0;
}



















