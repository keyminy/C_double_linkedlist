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
	loadDataFromFile(g_pList);
	while (1) {
		int breakFlag = 0;
		menu = PrintMenu();
		switch (menu) {
		case NEW:// 1 
		{
			printf("------------------ < �Է� ���� >----------------------\n");
			NODE* newNode = (NODE*)malloc(sizeof(NODE));
			scanf_new_data(newNode);
			
			printf("Ȯ�� (y/n) : ");
			scanf_s("%c%*c", &ch);
			if (ch == 'y') {
				if(SearchNode(newNode->roomno)){
					printf("�̹� ����� �����Դϴ�.\n");
				}
				else {
					AddNewNode(
						newNode->roomno
						, newNode->name
						, newNode->phone
						, newNode->price
						, newNode->address
						, &newNode->enter_date
						, &newNode->exit_date
					);
					printf("���� ���� �Ǿ����ϴ�.\n");
				}
			}
			_getch(); // Used just to pause the screen
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
			printf("------------------ < ���� ���� >----------------------\n");
			printf("roomno �Է� : ");
			scanf_s("%d%*c", &sel_roomNo);
			found = SearchNode(sel_roomNo);
			if (found != NULL) {
				printf("Ȯ�� (y/n) : ");
				scanf_s("%c%*c", &ch);
				if (ch == 'y') {
					printf("name : ");
					gets_s(found->name, sizeof(found->name));
					printf("phoneno : ");
					gets_s(found->phone, sizeof(found->phone));
					printf("price : ");
					scanf_s("%lf%*c", &found->price);
					printf("address : ");
					gets_s(found->address, sizeof(found->address));
					printf("Enter date(yyyy-mm-dd) : ");
					scanf_s("%[^-]-%[^-]-%s%*c"
						, found->enter_date.year, sizeof(found->enter_date.year)
						, found->enter_date.month, sizeof(found->enter_date.month)
						, found->enter_date.day, sizeof(found->enter_date.day));
					printf("Exit date(yyyy-mm-dd) : ");
					scanf_s("%[^-]-%[^-]-%s%*c"
						, found->exit_date.year, sizeof(found->exit_date.year)
						, found->exit_date.month, sizeof(found->exit_date.month)
						, found->exit_date.day, sizeof(found->exit_date.day));
					printf("���� ���� �Ǿ����ϴ�.\n");
				}
			}
			else {
				puts("���� ���� �Դϴ�.");
			}

			_getch(); // Used just to pause the screen
			break;
		case SEARCH: // 4
			printf("----------------------- < ��ȸ(������ȸ) >---------------------------\n");
			printf("roomno �Է� : ");
			scanf_s("%d%*c", &sel_roomNo);
			
			found = SearchNode(sel_roomNo);
			if (found != NULL) {
				printf("\nroomno : %d\n", found->roomno);
				printf("name : %s\n", found->name);
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
			printf("--------------< ���� >---------------------\n");
			printf("  �޴��� ����\n\n");
			printf("Ȯ��(y / n) : ");
			scanf_s("%c%*c", &ch);
			if (ch == 'y') {
				//  ���� ���� ������ ������ resversation.txt�� ������ �ϰ� ȭ���� ���� �Ѵ�.
				SaveListToFile();
				breakFlag = 1;
				ReleaseAllList();
			}
			break;
		default:
			break;
		} // END switch
		if (breakFlag == 1) break;
	}
	puts("Bye~!");
}