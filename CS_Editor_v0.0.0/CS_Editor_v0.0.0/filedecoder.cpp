#include "filedecoder.h"
#include <stdlib.h>
#include "stack.h"

#define PSIZE sizeof(PROCESS_DATA)
static FILE* startPoint = NULL;
static volatile bool stopp_all_threads = 0;
static volatile int max_threads = 0;
static volatile int threads_finish = 0;
static volatile int start = 0;
static volatile int end = 0;
static PROCESS_DATA* elemFirst = NULL;
void elemPrint(PROCESS_DATA& entry);
void WINAPI find_Start()
{
	FILE* f = startPoint;
	char c = getc(f);
	int scnt = 0;
	while ((c = getc(f)) != EOF) {
		if (c != '*') {
			if (scnt == 30) {
				start++;
			}
			if (scnt == 25) {
				end++;
			}
			scnt = 0;
		}
		if (c == '*')
			scnt++;
	}
	threads_finish++;
	return;
}
int elemMaxEntry(int x) {
	static int y = 0;
	return (y += x);
}
void elemPrint(PROCESS_DATA& entry) {
	printf("*** Data of entry number %i\n", entry.number);
	printf("\tCategories: %i\n", entry.cNum);
}
PROCESS_DATA* elemGotoX(int num) {
	printf("Max_elem: %i inp: %i \n", elemMaxEntry(0), num);
	/*
	if (num < 0)
	{
		printf("Spa%cvogel!!!\n", ss);
		return 0;
	}
	if (num >= elemMaxEntry(0)) {
		printf("Value to High!!!\n");
		return 0;
	}
	PROCESS_DATA* temp = NULL;
	temp = elemFirst;
	printf("First Addr : %p\n", elemFirst);
	printf("2.    Addr: %p\n", elemFirst->pNext);

	for (int i = 0; i != num; i++) {
		printf("Set Addr : %p\n", temp);
		printf("Next Addr: %p\n", temp->pNext);
		temp = temp->pNext;
		if (temp == NULL) {
			printf("Value to high x2!!\n");
			return 0;
		}
		elemPrint(*temp);
	}
	memcpy(&x, temp, PSIZE);
	printf("ADDR-Sent: %p\n", temp);

	return 1*/
	PROCESS_DATA* l=NULL;
	if(!(l=(PROCESS_DATA*)stack_num(num)))
		return NULL;
	printf("ADDR-Sent: %p\n", l);
	return l;
}


bool elemNew(PROCESS_DATA& entry) {
	/*PROCESS_DATA* tempe;
	PROCESS_DATA temp;
	tempe = (PROCESS_DATA*)malloc(PSIZE);
	if (tempe == NULL) {
		printf("Ram Full \"elemNew()\" %p!!!\n", tempe);
		return 0;
	}
	entry.pNext = NULL;
	memcpy(tempe, &entry, PSIZE);
	if (elemGotoX(elemMaxEntry(0) - 1, temp)) {
		temp.pNext = tempe;
	}
	else {
		elemFirst = tempe;
	}
	tempe->pNext = NULL;


	printf("\tFirst     : %p\n", elemFirst);
	printf("\tTemp      : %p\n", tempe);
	printf("\tTemp next : %p\n", tempe->pNext);
	printf("\tLast next : %p\n", temp.pNext);
	printf("\t2. entry  : %p\n", elemFirst->pNext);
	printf("\tEntry:\n");
	elemPrint(entry);
	printf("\n");
	elemMaxEntry(1);
	return 1;*/
	return (bool)stack_push(&entry, sizeof(PROCESS_DATA));
}

bool elemExample() {
	PROCESS_DATA entry;
	PROCESS_DATA temp;
	entry.cNum = 23;
	printf("ADDR-First: %p\n", entry);
	elemPrint(entry);

	if (!elemNew(entry)) {
		printf("New elem1\n");
		return 0;
	}
	entry.cNum = 24;
	elemPrint(entry);
	if (!elemNew(entry)) {
		printf("New elem2\n");
		return 0;
	}
	PROCESS_DATA* tempp=NULL;

	if (!(tempp= elemGotoX(0))) {
		printf("elemGotoX 0\n");
		return 0;
	}
	printf("ADDR0: %p\n", tempp);
	elemPrint(*tempp);
	tempp = NULL;
	if (!(tempp = elemGotoX(1))) {
		printf("elemGotoX 1\n");
		return 0;
	}
	printf("ADDR1: %p\n", tempp);
	elemPrint(*tempp);

	return 1;
}
void file_operater(char* path) {

	stopp_all_threads = 1;
	FILE* f;
	if ((f = fopen(path, "r")) == NULL) {
		printf("File couldn't open!\n");
		return;
	}
	startPoint = f;
	stopp_all_threads = 0;
	threads_finish = 0;
	max_threads = 1;

	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)find_Start, NULL, 0, NULL);
	while (max_threads != threads_finish) {
		printf("Finish: %1.2lf%%\r", percent(max_threads, threads_finish));
	}
	printf("Finish: %1.2lf%%\n", percent(max_threads, threads_finish));
	printf("Threads: %i\n", max_threads);
	fclose(f);
	startPoint = NULL;
	printf("Start's:%02i\n", start / 2);
	printf("End's:%02i\n", end / 2);

}
