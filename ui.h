#pragma once
typedef enum MY_MENU {
	NEW = 1,
	REMOVE, //2
	MODIFY, // 3
	SEARCH, // 4
	PRINT, // 5
	EXIT = 9
} MY_MENU;

MY_MENU PrintMenu(void);
void EventLoopRun(void);