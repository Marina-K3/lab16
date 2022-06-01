#include"Header.h"
int main() {
	setlocale(LC_ALL, "rus");
	int bol=1;
	Graph* graph=NULL;
	int choice, tops = 0, faces = 0;
	while (bol) {
		printf("\n\t����\n 1 - ���������� �����\n 2 - ���������� �������\n 3 - ������ � ����\n 4 - ������ �� �����\n 5 - ������� ��� ���� ����� �������\n 6 - ���������� ������� ��������������/���������\n 0 - �����\n ��� ����� - ");
		scanf_s("%d", &choice);
		switch (choice) {
		case 0: bol = 0;
			break;
		case 1:
		    {
				printf(" ������� �������� ���������� ������ - ");
				scanf_s("%d", &tops);
				printf(" ������� �������� ���������� ���� - ");
				scanf_s("%d", &faces);
				while (!check_data(tops, faces)) {
					printf(" �� ����� ������������ ���-�� ������ � ����\n");
					printf(" ������� �������� ���������� ������ - ");
					scanf_s("%d", &tops);
					printf(" ������� �������� ���������� ���� - ");
					scanf_s("%d", &faces);
				}
				graph = Create(graph, tops, faces);
				Print(graph, faces);
			}
				break;
			case 2: if (tops == 0 || faces == 0) printf(" ������� �������� ����\n");
				  else { 
					graph = AddTop(graph, tops, faces); 
					faces++;
					tops++;
					Print(graph, faces);
				  }
				break;
			case 3: if (graph == NULL) {
				printf("\t������ ���������� � ���� - ������� �������� ����\n");
			}else WriteToFile(graph, faces);
				break;
			case 4: ReadFromFile();
				break;
			case 5: 
				if (tops != 0) {
					int top;
					printf("\t������� ������� - ");
					scanf_s("%d", &top);
					while (!check_top(graph, top, tops)) {
						printf("\t�� ����� ������������ ��������\n");
						printf("\t������� ������� - ");
						scanf_s("%d", &top);
					}
					EdgesOfTop(graph, top, faces);
				}
				break;
			case 6: if (tops != 0 && faces != 0)
				CreateMatrix(graph, tops, faces);
				  else printf("\t������ ������� ������� ����� ��� ���������� ����� !\n");
				break;
		}
	}
}