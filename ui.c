#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "ui.h"
#include "list.h"

MY_MENU PrintMenu(void) {
	MY_MENU input = 0;
	system("cls"); //ȭ���ʱ�ȭ
	printf("------------------ < ���� ���� >----------------------\n");
	printf("1. �Է�(����)\n");
	printf("2. ����(���)\n");
	printf("3. ����(���೻������)\n");
	printf("4. ��ȸ(������ȸ)\n");
	printf("5. ��ü��ȸ(������ ������ȸ)\n\n");
	printf("9. ����\n\n");
	printf("Select : ");
	scanf_s("%d%*c", &input);
	return input;
}

void EventLoopRun(void) {
	MY_MENU menu = 0;
	char ch = 0;
	int sel_roomNo = 0;
	NODE* found = (NODE*)malloc(sizeof(NODE));
	while (1) {
		int breakFlag = 0;
		menu = PrintMenu();
		switch (menu) {
		case NEW:// 1 
		{
			_stDate enterDate = { "2024", "05", "15" };
			_stDate exitDate = { "2024", "05", "20" };
			AddNewNode(
				101
				, "kim"
				, "01012345678"
				, 100000
				, "seoul"
				, &enterDate
				, &exitDate
			);
			break;
		}
		case REMOVE: // 2 
			printf("--------------< ����(���) >---------------------\n");

			printf("����Ͻô� �� ��ȣ�� �Է����ּ���. \n");
			printf("roomno �Է� : ");
			scanf_s("%d%*c", &sel_roomNo);

			found = SearchNode(sel_roomNo);
			if (found != NULL) {
				printf("name : %s\n", found->name);
				printf("phoneno : %s\n\n", found->phone);
				printf("Ȯ�� (y/n) : ");
				scanf_s("%c%*c", &ch);
				if (ch == 'y') {
					RemoveNode(found);
				}
			}
			else {
				puts("���� ���� �Դϴ�.");
			}
			_getch(); // Used just to pause the screen
			break;
		case MODIFY: // 3

			_getch(); // Used just to pause the screen
			break;
		case SEARCH: // 4
			printf("----------------------- < ��ȸ(������ȸ) >---------------------------\n");
			printf("roomno �Է� : ");
			scanf_s("%d%*c", &sel_roomNo);
			
			found = SearchNode(sel_roomNo);
			if (found != NULL) {
				printf("\nroomno : %d\n", found->roomno);
				printf("name : %d\n", found->name);
				printf("phoneno : %s\n", found->phone);
				printf("��� : %.lf\n", found->price);
				printf("�ּ� : %s\n", found->address);
				printf("�Խ� : %s-%s-%s\n", &(found->enter_date.year), &(found->enter_date.month), &(found->enter_date.day));
				printf("��ǿ����ð� : %s-%s-%s\n", &(found->exit_date.year), &(found->exit_date.month), &(found->exit_date.day));
			}
			else {
				puts("���� ���� ��ȣ �Դϴ�.");
			}
			_getch(); // Used just to pause the screen
			break;
		case PRINT: // 5
			PrintAllList();
			break;
		case EXIT:
			breakFlag = 1;
			ReleaseAllList();
			break;
		default:
			break;
		} // END switch
		if (breakFlag == 1) break;
	}
	puts("Bye~!");
}