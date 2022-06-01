#pragma once
#include <stdio.h>
#include <stdlib.h>

// Define the  number of vertices in the graph
#define N 6

// Data structure to store a graph object
struct Graph
{
    // An array of pointers to Node to represent an adjacency list
    struct Node* head[N];
};

// Data structure to store adjacency list nodes of the graph
struct Node
{
    int dest, weight;
    struct Node* next;
};

// Data structure to store a graph edge
struct Edge {
    int src, dest, weight;
};
void CreateMatrix(struct Edge edges[], int n) {
    int mas[N][N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            mas[i][j] = 0;
        }
    }
    for (int i = 0; i < n; i++) {
        mas[edges[i].src - 1][edges[i].dest - 1] = edges[i].weight;
    }
    printf("\n    ");
    for (int i = 0; i < N; i++) {
        printf("(%d) ", i + 1);
    }
    printf("\n");
    for (int i = 0; i < N; i++) {
        printf("(%d) ", i + 1);
        for (int j = 0; j < N; j++) {
            printf(" %d  ", mas[i][j]);
        }
        printf("\n");
    }
}
// Function to create an adjacency list from specified edges
struct Graph* createGraph(struct Edge edges[], int n)
{
    // allocate storage for the graph data structure
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));

    // initialize head pointer for all vertices
    for (int i = 0; i < N; i++) {
        graph->head[i] = NULL;
    }

    // add edges to the directed graph one by one
    for (int i = 0; i < n; i++)
    {
        if (edges[i].dest != 0 && edges[i].weight != 0) {
            // get the source and destination vertex
            int src = edges[i].src;
            int dest = edges[i].dest;
            int weight = edges[i].weight;

            // allocate a new node of adjacency list from src to dest
            struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
            newNode->dest = dest;
            newNode->weight = weight;

            // point new node to the current head
            newNode->next = graph->head[src];

            // point head pointer to the new node
            graph->head[src] = newNode;
        }
    }

    return graph;
}

// Function to print adjacency list representation of a graph
void printGraph(struct Graph* graph)
{
    for (int i = 0; i < N; i++)
    {
        // print current vertex and all its neighbors
        struct Node* ptr = graph->head[i];
        while (ptr != NULL)
        {
            printf("%d -> %d (%d)\t", i, ptr->dest, ptr->weight);
            ptr = ptr->next;
        }

        printf("\n");
    }
}
//void Delete(struct Graph* graph) {
//    graph->head[4] = NULL;
//    for (int i = 0; i < N; i++) {
//        struct Node* ptr = graph->head[i];
//        while (ptr != NULL)
//        {
//            if (ptr->dest == 5) {
//
//            }
//            ptr = ptr->next;
//        }
//
//        printf("\n");
//    }
//}