#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<locale.>

int checkXY(int x, int y, struct Connections* con, int faces);

typedef struct Graph {
	int* Tops;//вершины
	char* Faces;//грани(рёбра)
	struct Connections *con;//описывающие их связи
};
typedef struct Connections {
	int given;//данная вершина (в которой находимся)
	int dest;//вершина с которой она соединяется
	char face;//ребро соединения
};
Graph* Create(Graph* graph, int tops, int faces) {
	graph = NULL;
	graph = (Graph*)malloc(sizeof(Graph));
	graph->Tops = (int*)malloc(tops*sizeof(int));
	graph->Faces = (char*)malloc(faces * sizeof(char));
	for (int i = 0; i < tops; i++) {
		graph->Tops[i] = i + 1;
	}
	for (int i = 65; i <65+faces; i++) {
		graph->Faces[i - 65] = i;
	}
	graph->con = (struct Connections*)malloc(faces * sizeof(struct Connections));
	printf(" Настраиваем связи между вершинами (рандомно)\n");
	for (int i = 0; i < faces; i++) {
		int x, y;
		x = rand() % tops + 1;
		y = rand() % tops + 1;
		while (!checkXY(x, y, graph->con, faces)) {
			x = rand() % tops + 1;
			y = rand() % tops + 1; 
		}
		graph->con[i].given = x;
		graph->con[i].dest = y;
		graph->con[i].face = graph->Faces[i];
	}
	system("pause");
	printf(" Успешное завершение создания графа !\n");
	return graph;
}
void Print(Graph* graph, int N) {
	if (graph) {
		printf("\n\t\tГраф:\n");
		for (int i = 0; i < N; i++) {
			printf(" %d --> %d (%c)\n", graph->con[i].given, graph->con[i].dest, graph->con[i].face);
		}
	}
	else printf(" Указатель на граф недействителен!");
}
int check_data(int tops, int faces) {
	if (tops < 2 || faces < 0) return 0;
	if (tops == 1) return 0;
	if (faces > tops * (tops - 1)) return 0;
	return 1;
}
int checkXY(int x, int y, Connections* con, int faces) {
	for (int i = 0; i < faces; i++) {
		if ((con[i].given== x && con[i].dest == y) || x==y) return 0;
	}
	return 1;
}

Graph* AddTop(Graph* graph, int tops, int faces) {
	graph->Tops = (int*)realloc(graph->Tops,(tops+1)* sizeof(int));
	graph->Faces = (char*)realloc(graph->Faces,(faces + 1) * sizeof(char));
	graph->con = (struct Connections*)realloc(graph->con,(faces + 1) * sizeof(struct Connections));
	graph->Tops[tops] = tops + 1;
	graph->Faces[faces] = 65 + faces;
	int x, y;
	x = graph->Tops[tops];
	y = rand() % tops + 1;
	while (!checkXY(x, y, graph->con, faces)) {
		y = rand() % tops + 1;
	}
	graph->con[faces].given = x;
	graph->con[faces].dest = y;
	graph->con[faces].face = graph->Faces[faces];
	return graph;
}
void WriteToFile(Graph* graph, int n) {
	FILE* file;
	file = fopen("Графы.txt", "w");
	if (file) {
		for (int i = 0; i < n; i++) {
			fprintf(file, "%d %d %c\n",graph->con[i].given,graph->con[i].dest, graph->con[i].face);
		}
		printf(" Запись прошла успешно !\n");
	}
	else printf("\tФайл не удалось открыть\n");
	fclose(file);
}
void ReadFromFile() {
	int given=0, dest=0;
	char face = '-', newline;
	FILE* file;
	file = fopen("Графы.txt", "r");
	if (file) {
		while (fscanf(file, "%d %d %c%c", &given, &dest, &face, &newline) && !feof(file)) {
			if(given!=0 && dest!=0 && face!='-')
			   printf("%d --> %d (%c)\n", given, dest, face);
		}
	}
	else printf("\tФайл не удалось открыть\n");
	if (given == 0 || dest == 0)
		printf(" Что-то пошло не так !\n");
}
void EdgesOfTop(Graph* graph, int top, int faces) {
	for (int i = 0; i <=faces; i++) {
		if (graph->con[i].given == top) {

			printf(" %d --> %d (%c)\n", graph->con[i].given, graph->con[i].dest, graph->con[i].face);
		}
	}
}
int check_top(Graph* graph, int top, int tops) {
	if (top < 1 || top>tops) return 0;
	return 1;
}
void CreateMatrix(Graph* graph,int tops, int faces) {
	int choice;
	printf(" 1 - смежности 2 - инциндентности\n ваш выбор - ");
	scanf_s("%d", &choice);
	while (choice > 2 || choice < 1) {
		printf(" Вы ввели некорректное значение. Заново - ");
		scanf_s("%d", &choice);
	}
	if(choice==1){
		char** m_smegnosti;
		m_smegnosti = (char**)malloc(tops * sizeof(char*));
		for (int i = 0; i < tops; i++) {
			m_smegnosti[i] = (char*)malloc(tops * sizeof(char));
		}
		for (int i = 0; i < tops; i++) {
			for (int j = 0; j < tops; j++) {
				m_smegnosti[i][j] = '-';
			}
		}
		for (int i = 0; i < faces; i++) {
			m_smegnosti[graph->con[i].given - 1][graph->con[i].dest - 1] = graph->con[i].face;
		}
		printf("    ");
		for (int i = 0; i < tops; i++) {
			printf("(%d) ", i + 1);
		}
		printf("\n");
		for (int i = 0; i < tops; i++) {
			printf("(%d) ", i + 1);
			for (int j = 0; j < tops; j++) {
				printf(" %c  ", m_smegnosti[i][j]);
			}
			printf("\n");
		}
	}
	if(choice==2){
		int** m_incindent;
		m_incindent = (int**)malloc(tops * sizeof(int*));
		for (int i = 0; i < tops; i++) {
			m_incindent[i] = (int*)malloc(faces * sizeof(int));
		}
		for (int i = 0; i < tops; i++) {
			for (int j = 0; j < faces; j++) {
				m_incindent[i][j] = 0;
			}
		}
		for (int i = 0; i < faces; i++) {
			m_incindent[graph->con[i].given - 1][graph->con[i].face - 65] = 1;
		}
		printf("    ");
		for (int j = 65; j < 65+faces; j++) {
			printf(" %c ", j);
		}
		printf("\n");
		for (int i = 0; i < tops; i++) {
			printf("(%d) ", i + 1);
			for (int j = 0; j < faces; j++) {
				printf(" %d ", m_incindent[i][j]);
			}
			printf("\n");
		}
	}
}