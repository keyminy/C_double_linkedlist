#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include "list.h"


NODE g_HeadNode = { 0,"__Dummy Head__" };
NODE g_TailNode = { 0,"__Dummy Tail__" };
LIST* g_pList;

void Init_Dummy_Head_And_Tail() {
	g_HeadNode.next = &g_TailNode;
	g_TailNode.prev = &g_HeadNode;
}

LIST* CreatList() {
	g_pList = (LIST*)malloc(sizeof(LIST));
	g_pList->head = &g_HeadNode;
	g_pList->tail = &g_TailNode;
	g_pList->curr = NULL;
	g_pList->numOfData = 0;
	return g_pList;
}

void AddNewNode(int roomno,
    const char* pszName,const char* pszPhone,
    double price,const char* pszAddress,
    const _stDate* enterDate,
	const _stDate* exitDate) {
	
	//add new node
	NODE* pNewNode = (NODE*)malloc(sizeof(NODE));
	pNewNode->roomno = roomno;
	strcpy_s(pNewNode->name,sizeof(pNewNode->name), pszName);
	strcpy_s(pNewNode->phone, sizeof(pNewNode->phone), pszPhone);
	pNewNode->price = price;
	strcpy_s(pNewNode->address, sizeof(pNewNode->address), pszAddress);
	pNewNode->enter_date = *enterDate;
	pNewNode->exit_date = *exitDate;
	pNewNode->prev = NULL;
	pNewNode->next = NULL;

	//Insert new node
	//Currently, the dummy head value is the prev node of the dummy tail.
	NODE* pPrevNode = g_TailNode.prev;
	// The 1,2 courses
	pNewNode->prev = pPrevNode;
	pNewNode->next = &g_TailNode;
	// The 3,4 courses
	pPrevNode->next = pNewNode;
	g_TailNode.prev = pNewNode;
	g_pList->numOfData++;
}

void PrintAllList(void) {
	if (g_pList->numOfData >= 1) {
		g_pList->curr = g_pList->head->next;
		printf("----------------------- < 전체조회(예약자 전체조회) >---------------------------\n");
		printf("roomno\tname\tphoneno      \t요금     \t주소  \t\t입실      \t퇴실        \n");
		printf("------\t----\t-------------\t--------\t-------\t\t---------\t-----------\n");
		while (g_pList->curr != NULL && g_pList->curr != g_pList->tail) {
			printf("%-6d\t%-4s\t%-13s\t%-8.0f\t%-6s\t"
				, g_pList->curr->roomno
				, g_pList->curr->name
				, g_pList->curr->phone
				, g_pList->curr->price
				, g_pList->curr->address);
			printf("%-4s-%-2s-%-2s\t%-4s-%-2s-%-2s\n"
				, g_pList->curr->enter_date.year
				, g_pList->curr->enter_date.month
				, g_pList->curr->enter_date.day
				, g_pList->curr->exit_date.year
				, g_pList->curr->exit_date.month
				, g_pList->curr->exit_date.day);
			g_pList->curr = g_pList->curr->next;
		}
		putchar('\n');

	}
	else {
		printf("No data to print\n");
	}
	printf("=========================================================================\n");
	_getch(); // Used just to pause the screen
}

void ReleaseAllList(void) {
	g_pList->curr = g_pList->head->next;
	NODE* pDelete = NULL; // Used to delete a node
	while (g_pList->curr != NULL && g_pList->curr != g_pList->tail) {
		pDelete = g_pList->curr;
		g_pList->curr = g_pList->curr->next;
		printf("Deleted!!=================\n");
		printf("roomno:%d, name:%s, phone:%s, price:%d, address:%s, enter_date:%s-%s-%s, exit_date:%s-%s-%s\n"
			, pDelete->roomno
			, pDelete->name
			, pDelete->phone
			, pDelete->price
			, pDelete->address
			, pDelete->enter_date.year
			, pDelete->enter_date.month
			, pDelete->enter_date.day
			, pDelete->exit_date.year
			, pDelete->exit_date.month
			, pDelete->exit_date.day
			);
		free(pDelete);
		g_pList->numOfData--;
	}
	Init_Dummy_Head_And_Tail();
}

void scanf_new_data(NODE* pNewNode) {
	printf("roomno: ");
	scanf_s("%d%*c", &pNewNode->roomno);
	printf("name : ");
	gets_s(pNewNode->name, sizeof(pNewNode->name));
	printf("phone number : ");
	gets_s(pNewNode->phone, sizeof(pNewNode->phone));
	printf("price : ");
	scanf_s("%lf%*c", &pNewNode->price);
	printf("Address : ");
	gets_s(pNewNode->address, sizeof(pNewNode->address));
	printf("Enter date(yyyy-mm-dd) : ");
	scanf_s("%[^-]-%[^-]-%s%*c"
		, pNewNode->enter_date.year, sizeof(pNewNode->enter_date.year)
		, pNewNode->enter_date.month, sizeof(pNewNode->enter_date.month)
		, pNewNode->enter_date.day, sizeof(pNewNode->enter_date.day));
	printf("Exit date(yyyy-mm-dd) : ");
	scanf_s("%[^-]-%[^-]-%s%*c"
		, pNewNode->exit_date.year, sizeof(pNewNode->exit_date.year)
		, pNewNode->exit_date.month, sizeof(pNewNode->exit_date.month)
		, pNewNode->exit_date.day, sizeof(pNewNode->exit_date.day));
}

NODE* SearchNode(int roomno) {
	g_pList->curr = g_pList->head->next;
	while (g_pList->curr != NULL && g_pList->curr != g_pList->tail) {
		if (g_pList->curr->roomno == roomno) {
			return g_pList->curr;
		}
		g_pList->curr = g_pList->curr->next;
	}
	return NULL;
}

void RemoveNode(NODE* pRemove) {
	NODE* pPrev = pRemove->prev;
	NODE* pNext = pRemove->next;
	pPrev->next = pRemove->next;
	pNext->prev = pRemove->prev;

	printf("RemoveNode() : %s\n", pRemove->name);
	free(pRemove);
	g_pList->numOfData--;
}

//현재 예약 정보의 내용을 resversation.txt에 저장을 하고 화면을 종료 한다.
void SaveListToFile() {
	FILE* fp = NULL;
	fopen_s(&fp, "reservation.txt", "wb");
	if (fp == NULL) {
		puts("File open error");
		return;
	}
	g_pList->curr = g_pList->head->next;
	while (g_pList->curr != NULL && g_pList->curr != g_pList->tail) {
		fprintf(fp, "%-6d\t%-4s\t%-13s\t%-8.0f\t%-6s\t"
			, g_pList->curr->roomno
			, g_pList->curr->name
			, g_pList->curr->phone
			, g_pList->curr->price
			, g_pList->curr->address);
		fprintf(fp, "%-4s-%-2s-%-2s\t%-4s-%-2s-%-2s\n"
			, g_pList->curr->enter_date.year
			, g_pList->curr->enter_date.month
			, g_pList->curr->enter_date.day
			, g_pList->curr->exit_date.year
			, g_pList->curr->exit_date.month
			, g_pList->curr->exit_date.day);
		g_pList->curr = g_pList->curr->next;
	}
	fclose(fp);
}

void loadDataFromFile(LIST* g_pList) {
	g_pList->curr = g_pList->head->next;
	FILE* fp = NULL;
	fopen_s(&fp, "reservation.txt", "rb");
	if (fp == NULL) {
		puts("File open error");
		return;
	}
	rewind(fp); // 스트림의 위치 지정자를 맨 처음으로 설정한다.
	while (1) {
		NODE* newNode = (NODE*)malloc(sizeof(NODE));
		int ret = fscanf(fp,
			"%d %[^\t] %[^\t] %lf %[^\t] %[^-]-%[^-]-%s %[^-]-%[^-]-%s%*c"
			, &newNode->roomno
			, newNode->name
			, newNode->phone
			, &newNode->price
			, newNode->address
			, newNode->enter_date.year
			, newNode->enter_date.month
			, newNode->enter_date.day
			, newNode->exit_date.year
			, newNode->exit_date.month
			, newNode->exit_date.day);
		if (ret == EOF) {
			free(newNode);
			break;
		}
		AddNewNode(
			newNode->roomno
			, newNode->name
			, newNode->phone
			, newNode->price
			, newNode->address
			, &newNode->enter_date
			, &newNode->exit_date
		);
		g_pList->numOfData++;
	}
	fclose(fp);
}