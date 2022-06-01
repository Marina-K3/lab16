#include"Header.h"
int main() {
	setlocale(LC_ALL, "rus");
	int bol=1;
	Graph* graph=NULL;
	int choice, tops = 0, faces = 0;
	while (bol) {
		printf("\n\tМЕНЮ\n 1 - Заполнение графа\n 2 - Добавление вершины\n 3 - Запись в файл\n 4 - Чтение из файла\n 5 - Вывести все цепи одной вершины\n 6 - Построение матрицы инциндентности/смежности\n 0 - Выход\n ваш выбор - ");
		scanf_s("%d", &choice);
		switch (choice) {
		case 0: bol = 0;
			break;
		case 1:
		    {
				printf(" Введите желаемое количество вершин - ");
				scanf_s("%d", &tops);
				printf(" Введите желаемое количество рёбер - ");
				scanf_s("%d", &faces);
				while (!check_data(tops, faces)) {
					printf(" Вы ввели несочетаемое кол-во вершин и рёбер\n");
					printf(" Введите желаемое количество вершин - ");
					scanf_s("%d", &tops);
					printf(" Введите желаемое количество рёбер - ");
					scanf_s("%d", &faces);
				}
				graph = Create(graph, tops, faces);
				Print(graph, faces);
			}
				break;
			case 2: if (tops == 0 || faces == 0) printf(" Сначала создайте граф\n");
				  else { 
					graph = AddTop(graph, tops, faces); 
					faces++;
					tops++;
					Print(graph, faces);
				  }
				break;
			case 3: if (graph == NULL) {
				printf("\tНечего записывать в файл - сначала создайте граф\n");
			}else WriteToFile(graph, faces);
				break;
			case 4: ReadFromFile();
				break;
			case 5: 
				if (tops != 0) {
					int top;
					printf("\tВведите вершину - ");
					scanf_s("%d", &top);
					while (!check_top(graph, top, tops)) {
						printf("\tВы ввели некорректное значение\n");
						printf("\tВведите вершину - ");
						scanf_s("%d", &top);
					}
					EdgesOfTop(graph, top, faces);
				}
				break;
			case 6: if (tops != 0 && faces != 0)
				CreateMatrix(graph, tops, faces);
				  else printf("\tНельзя создать матрицу графа без созданного графа !\n");
				break;
		}
	}
}