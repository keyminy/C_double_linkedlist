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
			printf("--------------< 삭제(퇴실) >---------------------\n");

			printf("퇴실하시는 방 번호를 입력해주세요. \n");
			printf("roomno 입력 : ");
			scanf_s("%d%*c", &sel_roomNo);

			found = SearchNode(sel_roomNo);
			if (found != NULL) {
				printf("name : %s\n", found->name);
				printf("phoneno : %s\n\n", found->phone);
				printf("확인 (y/n) : ");
				scanf_s("%c%*c", &ch);
				if (ch == 'y') {
					RemoveNode(found);
				}
			}
			else {
				puts("없는 객실 입니다.");
			}
			_getch(); // Used just to pause the screen
			break;
		case MODIFY: // 3

			_getch(); // Used just to pause the screen
			break;
		case SEARCH: // 4
			printf("----------------------- < 조회(개별조회) >---------------------------\n");
			printf("roomno 입력 : ");
			scanf_s("%d%*c", &sel_roomNo);
			
			found = SearchNode(sel_roomNo);
			if (found != NULL) {
				printf("\nroomno : %d\n", found->roomno);
				printf("name : %d\n", found->name);
				printf("phoneno : %s\n", found->phone);
				printf("요금 : %.lf\n", found->price);
				printf("주소 : %s\n", found->address);
				printf("입실 : %s-%s-%s\n", &(found->enter_date.year), &(found->enter_date.month), &(found->enter_date.day));
				printf("퇴실예정시각 : %s-%s-%s\n", &(found->exit_date.year), &(found->exit_date.month), &(found->exit_date.day));
			}
			else {
				puts("없는 객실 번호 입니다.");
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