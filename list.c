#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "list.h"

NODE g_HeadNode = {0};
NODE g_TailNode = {0};

void InitList() {
	g_HeadNode.next = &g_TailNode;
	g_TailNode.prev = &g_HeadNode;
}