#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "ui.h"
#include "list.h"



int main() {
	Init_Dummy_Head_And_Tail();
	g_pList = CreatList();
	EventLoopRun();
	return 0;
}