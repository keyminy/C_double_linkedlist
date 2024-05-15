#pragma once
typedef struct {
	char year[8];
	char month[4];
	char day[4];
} _stDate;

typedef struct _node {
	int roomno;
	char name[20];
	char phone[40];
	double price;
	char address[40];
	_stDate enter_date;
	_stDate exit_date;
	struct _node* prev;
	struct _node* next;
} NODE;

typedef struct {
	NODE* head;
	NODE* tail;
	NODE* curr;
	int numOfData;
} LIST;

extern NODE g_HeadNode;
extern NODE g_TailNode;
extern LIST* g_pList;


void Init_Dummy_Head_And_Tail(void);
void AddNewNode(int roomno,
	const char* pszName, const char* pszPhone,
	double price, const char* pszAddress,
	const _stDate* enterDate,
	const _stDate* exitDate);
void PrintAllList(void);
void ReleaseAllList(void);
LIST* CreatList();
void scanf_new_data(NODE* pNewNode);
NODE* SearchNode(int roomno);
void RemoveNode(NODE* pNode);