#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "ui.h"

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
	while ((menu = PrintMenu()) != EXIT) {
		switch (menu) {
		case NEW:
			break;
		case REMOVE:
			break;
		case MODIFY:
			break;
		case SEARCH:
			break;
		case PRINT:
			break;
		default:
			break;
		}
	}
	puts("Bye~!");
}