#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "ui.h"
#include "list.h"

MY_MENU PrintMenu(void) {
	MY_MENU input = 0;
	system("cls"); //화면초기화
	printf("------------------ < 객실 관리 >----------------------\n");
	printf("1. 입력(예약)\n");
	printf("2. 삭제(퇴실)\n");
	printf("3. 수정(예약내역수정)\n");
	printf("4. 조회(개별조회)\n");
	printf("5. 전체조회(예약자 전쳬조회)\n\n");
	printf("9. 종료\n\n");
	printf("Select : ");
	scanf_s("%d%*c", &input);
	return input;
}

void EventLoopRun(void) {
	MY_MENU menu = 0;
	while (1) {
		int breakFlag = 0;
		menu = PrintMenu();
		switch (menu) {
		case NEW: {
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
		}
			break;
		case REMOVE:
			ReleaseAllList();
			break;

		case MODIFY:
			break;
		case SEARCH:
			break;
		case PRINT:
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