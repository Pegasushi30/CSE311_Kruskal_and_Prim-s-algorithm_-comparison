#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

// Comparator function to use in sorting
int comparator(const void* p1, const void* p2)
{
    const int(*x)[3] = p1;
    const int(*y)[3] = p2;

    return (*x)[2] - (*y)[2];
}

// Initialization of parent[] and rank[] arrays
void makeSet(int parent[], int rank[], int n)
{
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

// Function to find the parent of a node
int findParent(int parent[], int component)
{
    if (parent[component] == component)
        return component;

    return parent[component] = findParent(parent, parent[component]);
}

// Function to unite two sets
void mergeSets(int u, int v, int parent[], int rank[])
{
    // Finding the parents
    u = findParent(parent, u);
    v = findParent(parent, v);

    if (rank[u] < rank[v]) {
        parent[u] = v;
    }
    else if (rank[u] > rank[v]) {
        parent[v] = u;
    }
    else {
        parent[v] = u;

        // Since the rank increases if
        // the ranks of two sets are the same
        rank[u]++;
    }
}

// Function to find the MST
void kruskalAlgo(int n, int **graph, int ***mst_edges)
{
    int numEdges = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (graph[i][j] != 0)
                numEdges++;
        }
    }

    int (*edge)[3] = malloc(numEdges * sizeof(int[3]));
    if (edge == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    int index = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (graph[i][j] != 0) {
                edge[index][0] = i;
                edge[index][1] = j;
                edge[index][2] = graph[i][j];
                index++;
            }
        }
    }

    // First we sort the edge array in ascending order
    // so that we can access minimum distances/cost
    qsort(edge, numEdges, sizeof(edge[0]), comparator);

    int* parent = malloc(n * sizeof(int));
    int* rank = malloc(n * sizeof(int));

    // Function to initialize parent[] and rank[]
    makeSet(parent, rank, n);

    // To store the minimum cost
    int minCost = 0;

    // Allocate memory for the edges of the MST
    *mst_edges = malloc((n - 1) * sizeof(int*));
    for (int i = 0; i < n - 1; i++) {
        (*mst_edges)[i] = malloc(3 * sizeof(int));
    }

    int selectedEdges = 0;
    for (int i = 0; i < numEdges; i++) {
        int v1 = findParent(parent, edge[i][0]);
        int v2 = findParent(parent, edge[i][1]);
        int wt = edge[i][2];

        // If the parents are different, that
        // means they are in different sets, so
        // merge them
        if (v1 != v2) {
            mergeSets(v1, v2, parent, rank);
            minCost += wt;

            // Store the original vertices in the mst_edges array
            (*mst_edges)[selectedEdges][0] = edge[i][0]; // not v1
            (*mst_edges)[selectedEdges][1] = edge[i][1]; // not v2
            (*mst_edges)[selectedEdges][2] = wt;

            selectedEdges++;
            if (selectedEdges == n - 1)
                break;
        }
    }

    free(edge);
    free(parent);
    free(rank);
}

// Driver code
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
    for(int i = 0; i < n; i++) {
        graph[i] = malloc(n * sizeof(int));
        if (graph[i] == NULL) {
            printf("Memory allocation failed.\n");
            return 1;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (fscanf(inputFile, "%d", &graph[i][j]) != 1) {
                printf("Failed to read the weights of the edges.\n");
                // Free the graph array
                for (int k = 0; k <= i; k++)
                    free(graph[k]);
                free(graph);
                fclose(inputFile);
                return 1;
            }
        }
    }

    fclose(inputFile);

    clock_t start, end;
    double execution_time;
    double execution_time1;
    double execution_time2;
    double execution_time3;
    double execution_time4;
    int **mst_edges;

    start = clock();
    kruskalAlgo(n, graph, &mst_edges);
    end = clock();
    execution_time = ((double) (end - start)) / CLOCKS_PER_SEC* 1000.0;
    printf("1st run (discarded) %lf ms\n",execution_time);

    start = clock();
    kruskalAlgo(n, graph, &mst_edges);
    end = clock();
    execution_time1 = ((double) (end - start)) / CLOCKS_PER_SEC* 1000.0;
    printf("2nd run  %lf ms\n",execution_time1);

    start = clock();
    kruskalAlgo(n, graph, &mst_edges);
    end = clock();
    execution_time2 = ((double) (end - start)) / CLOCKS_PER_SEC* 1000.0;
    printf("3rd run  %lf ms\n",execution_time2);

    start = clock();
    kruskalAlgo(n, graph, &mst_edges);
    end = clock();
    execution_time3 = ((double) (end - start)) / CLOCKS_PER_SEC* 1000.0;
    printf("4th run  %lf ms\n",execution_time3);

    start = clock();
    kruskalAlgo(n, graph, &mst_edges);
    end = clock();
    execution_time4 = ((double) (end - start)) / CLOCKS_PER_SEC* 1000.0;
    printf("5th run  %lf ms\n",execution_time4);

    double average=(execution_time1+execution_time2+execution_time3+execution_time4)/4;
    printf("Average runtime is %lf ms\n",average);
    // Print the edges of the MST
    //printf("Edges in the minimum spanning tree:\n");
    for (int i = 0; i < n - 1; i++) {
        //printf("%d -- %d == %d\n", mst_edges[i][0], mst_edges[i][1], mst_edges[i][2]);
        free(mst_edges[i]);
    }
    free(mst_edges);

    for (int i = 0; i < n; i++)
        free(graph[i]);
    free(graph);

    return 0;
}














   


