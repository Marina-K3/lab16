#include"Graph.h"
#include<locale.h>
int main() {
    setlocale(LC_ALL, "Rus");
    // input array containing edges of the graph (as per the above diagram)
   // (x, y, w) tuple represents an edge from x to y having weight `w`
    struct Edge edges[] =
    {
        {1,3,1}, {1, 2, 7}, {2, 6,1}, {2, 4, 4}, {3, 2, 5}, {3,6,4}, {3,5,2}, {5,2,2}, {6,5,3}, {5,4,5}
    };

    // calculate the total number of edges
    int n = sizeof(edges) / sizeof(edges[0]);

    // construct a graph from the given edges
    struct Graph* graph = createGraph(edges, n);
    printf("   Граф уже построен... Вам не нужно его вводить\n");
    system("pause");
    bool choice = true;
    while (choice) {
        system("cls");
        printf("\t\tМЕНЮ\n\t1 - Удалить рёбра с весом 4\n\t2 - Удалить вершину №5\n\t3 - Вывести граф\n\t4 - Построить матрицу смежности\n\t0 - Выйти\n\t");
        int user_choice;
        scanf_s("%d", &user_choice);
        while (user_choice < 0 || user_choice>4) {
            printf(" Вы неправильно выбрали ! Ещё одна попытка - ");
            scanf_s("%d", &user_choice);
        }
        switch (user_choice) {
        case 1:
            for (int i = 0; i < n; i++) {
                if (edges[i].weight == 4) {
                    edges[i].weight = 0;
                }
            }
            n = sizeof(edges) / sizeof(edges[0]);
            graph = createGraph(edges, n);
            system("pause");
            break;
        case 2:
            for (int i = 0; i < n; i++) {
                if (edges[i].dest == 5) {
                    edges[i].dest = 0;
                }
                if (edges[i].src == 5) {
                    edges[i].weight = 0;
                }
            }
            n = sizeof(edges) / sizeof(edges[0]);
            graph = createGraph(edges, n);
            system("pause");
            break;
        case 0:
            choice = false;
            break;
        case 3:// Function to print adjacency list representation of a graph
            printGraph(graph);
            system("pause");
            break;
        case 4:
            CreateMatrix(edges, n);
            system("pause");
            break;
        }
    }
    return 0;
}