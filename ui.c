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
	loadDataFromFile(g_pList);
	while (1) {
		int breakFlag = 0;
		menu = PrintMenu();
		switch (menu) {
		case NEW:// 1 
		{
			printf("------------------ < 입력 예약 >----------------------\n");
			NODE* newNode = (NODE*)malloc(sizeof(NODE));
			scanf_new_data(newNode);
			
			printf("확인 (y/n) : ");
			scanf_s("%c%*c", &ch);
			if (ch == 'y') {
				if(SearchNode(newNode->roomno)){
					printf("이미 예약된 객실입니다.\n");
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
					printf("정상 예약 되었습니다.\n");
				}
			}
			_getch(); // Used just to pause the screen
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
			printf("------------------ < 수정 예약 >----------------------\n");
			printf("roomno 입력 : ");
			scanf_s("%d%*c", &sel_roomNo);
			found = SearchNode(sel_roomNo);
			if (found != NULL) {
				printf("확인 (y/n) : ");
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
					printf("정상 수정 되었습니다.\n");
				}
			}
			else {
				puts("없는 객실 입니다.");
			}

			_getch(); // Used just to pause the screen
			break;
		case SEARCH: // 4
			printf("----------------------- < 조회(개별조회) >---------------------------\n");
			printf("roomno 입력 : ");
			scanf_s("%d%*c", &sel_roomNo);
			
			found = SearchNode(sel_roomNo);
			if (found != NULL) {
				printf("\nroomno : %d\n", found->roomno);
				printf("name : %s\n", found->name);
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
			printf("--------------< 종료 >---------------------\n");
			printf("  메뉴를 종료\n\n");
			printf("확인(y / n) : ");
			scanf_s("%c%*c", &ch);
			if (ch == 'y') {
				//  현재 예약 정보의 내용을 resversation.txt에 저장을 하고 화면을 종료 한다.
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