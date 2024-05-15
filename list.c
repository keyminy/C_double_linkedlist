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
	if (pNewNode == NULL) {
		printf("Memory allocation failed\n");
		return;
	}
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
	g_pList->numOfData++; // amazing...!
}

void PrintAllList(void) {
	if (g_pList->numOfData >= 1) {
		g_pList->curr = g_pList->head->next;
		printf("----------------------- < 전체조회(예약자 전체조회) >---------------------------\n");
		printf("roomno\tname\tphoneno      \t요금     \t주소    \t입실      \t퇴실        \n");
		printf("------\t----\t-------------\t--------\t-------\t\t---------\t-----------\n");
		while (g_pList->curr != g_pList->tail) {
			printf("%-6d\t%-4s\t%-13s\t%-8.2f\t%-6s\t"
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
	}
	Init_Dummy_Head_And_Tail();
}