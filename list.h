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
