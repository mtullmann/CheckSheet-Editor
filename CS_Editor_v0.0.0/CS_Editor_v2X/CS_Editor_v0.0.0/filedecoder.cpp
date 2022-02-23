#include "filedecoder.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;
#include "stack.h"

#define PSIZE sizeof(PROCESS_DATA)
static FILE* startPoint = NULL;
static volatile bool stopp_all_threads = 0;
static volatile int max_threads = 1;
static volatile int threads_finish = 0;
static volatile int start = 0;
static volatile int ende = 0;
static vector<PROCESS_DATA> elemFirst;
void elemPrint(PROCESS_DATA* entry);
bool elemNew(PROCESS_DATA& entry) {
	static long i = 0;
	entry.number = i++;
	elemFirst.push_back(entry);
	return 1;
}
void WINAPI find_Start()
{
	FILE* f = startPoint;
	char c = getc(f);
	PROCESS_DATA temp;
	int scnt = 0;
	int chrCnt = 0;
	bool flip;
	while ((c = getc(f)) != EOF) {
		if (c != '*') {
			if (scnt == 25) {
				start++;
				temp.cStart = *f;
				 chrCnt = 0;
			}
			if (scnt == 30) {
				ende++;
				temp.charlength=chrCnt;
				elemNew(temp);
			}
			chrCnt++;
			scnt = 0;
		}
		if (c == '*')
			scnt++;
	}
	threads_finish++;
	return;
}
void WINAPI start_decoding() {
	static int nr = 0;
	 int intern_nr = 0;
	nr++;
	intern_nr = nr - 1;
	printf("Start decode %i\n", intern_nr);
	FILE* f = 0;
	f =(FILE*) malloc(sizeof(FILE));
	f=elemFirst[intern_nr].cStart;
	for (int i = 0; i != elemFirst[intern_nr].charlength; i++) {
		printf("%c", fgetc(f));
	}
	
	Sleep(1000+100*(intern_nr*5));
	threads_finish++;
}
int elemMaxEntry(int x=0) {
	return elemFirst.size();
}
void elemPrint(PROCESS_DATA* entry) {
	if (entry == NULL)
		return;
	printf("*** Data of entry number %i\n", entry->number);
	printf("\tCategories: %i\n", entry->cNum);
	printf("\tName: %s\n", entry->cNames);
	printf("\tNote: %s\n", entry->note);

}
PROCESS_DATA* elemGotoX(int num) {
	printf("Max_elem: %i inp: %i \n", elemMaxEntry(0), num);

	if (num < 0)
	{
		printf("Spa%cvogel!!!\n", ss);
		return NULL;
	}
	if (num >= elemMaxEntry()) {
		printf("Value to High!!!\n");
		return NULL;
	}
	return &elemFirst[num];
}




bool elemExample() {
	PROCESS_DATA entry;
	PROCESS_DATA temp;
	entry.cNum = 23;
	entry.cNames = "Hallo";
	entry.cNames = "Hallo";
	elemNew(entry);

	entry.cNames = "Hallo Du";
	entry.note = "Du da";
	elemNew(entry);
	elemPrint(elemGotoX(0));
	elemPrint(elemGotoX(1));

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
	threads_finish = 0;
	startPoint = NULL;
	printf("Start's:%02i\n", start / 2);
	printf("End's:%02i\n", ende / 2);
	color(GRUENh);
	printf("\tElements Found %i\n\n\n",elemFirst.size());
	for (long i = 0; elemFirst.size() != i;i++) {
		printf("\t**Start Addr: %p\n", elemFirst[i].cStart);
		printf("\tStart cnt %i\n", elemFirst[i].charlength);
	}
	rcolor;
	printf("Decode Data...\n");
	max_threads=elemFirst.size();
	for (int i = 0; i != max_threads; i++) {
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)start_decoding, NULL, 0, NULL);
	}
	while (max_threads != threads_finish) {
		printf("Finish: %1.2lf%%\r", percent(max_threads, threads_finish));
	}
}
