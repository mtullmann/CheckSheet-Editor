
#include "stdio.h"
#include "stdlib.h"
#include "stack.h"
//#include "stdafx.h"
typedef struct StackNode
{
	void* pdat;
	StackNode* pNext;
} StackNode;
StackNode* pTop = NULL;

void stack_init() {
	pTop = NULL;
}
int stacksize() {
	int i = 0;
	StackNode* pCurr = pTop;
	while (pCurr != NULL) {
		pCurr = pCurr->pNext;
		i++;
	}
	return i;
}
int stack_push(void* p, int size) {
	StackNode* pNode = NULL;
	pNode = (StackNode*)malloc(size);
	if (pNode == NULL) {
		return 0;
	}
	pNode->pdat = p;
	pNode->pNext = pTop;
	pTop = pNode;
	return 1;
}
int stack_pop() {
	StackNode* pTemp = NULL;
	if (pTop == NULL) {
		return 0;
	}
	pTemp = pTop->pNext;
	//free(pTemp->pdat);
	free(pTop);
	pTop = pTemp;
	return 1;
}
int stack_remove() {
	if (pTop == NULL)return 0;
	while (pTop != NULL) {
		stack_pop();
	}
	return 1;
}
int stack_emty() {
	return (int)(pTop == NULL);
}
void* stack_front() {
	if (stack_emty())return NULL;
	return  pTop->pdat;
}
void* stack_num(int num) {
	StackNode* temp = pTop;
	if (temp == NULL)
		return NULL;
	printf("%p top ADDR\n", temp->pdat);
	printf("%p top Next ADDR\n", (temp->pNext)->pdat);
	for (int i = 0; i != num; i++)
	{
		if (temp == NULL) {
			printf("EXT\n");
			return NULL;
		}
		temp = temp->pNext;

	}
	printf("%p out ADDR\n", temp->pdat);

	return temp->pdat;
}