#include "filedecoder.h"

#define PSIZE sizeof(PROCESS_DATA)
static FILE* startPoint = NULL;
static volatile bool stopp_all_threads = 0;
static volatile int max_threads = 0;
static volatile int threads_finish = 0;
static volatile int start = 0;
static volatile int end = 0;
static PROCESS_DATA* elemFirst = NULL;
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
bool elemGotoX(int num, PROCESS_DATA* x) {
	if (num < 0)
	{
		printf("Spa%cvogel!!!\n", ss);
		return 0;
	}
	if (num > elemMaxEntry(0) + 1) {
		return 0;
	}
	PROCESS_DATA* temp = NULL;
	temp = elemFirst;
	for (int i = 0; i != num; i++) {
		temp = temp->pNext;
		if (temp == NULL)
			return 0;
	}
	x = temp;
	return 1;
}
bool elemNew(PROCESS_DATA* entry) {
	PROCESS_DATA* tempe = (PROCESS_DATA*)malloc(PSIZE);
	PROCESS_DATA* temp = NULL;
	if (tempe == NULL)
		return 0;
	elemGotoX(elemMaxEntry(0), temp);
	memcpy(entry, tempe, PSIZE);
	tempe->pNext = NULL;
	if (temp != NULL)
		temp->pNext = tempe;
	else
		elemFirst = tempe;
	elemMaxEntry(1);
	return 1;
}
void elemPrint(PROCESS_DATA* entry) {
	printf("*** Data of entry number %i\n", entry->number);
	printf("\tCategories: %i\n", entry->cNum);
}
bool elemExample() {
	PROCESS_DATA entry;
	PROCESS_DATA* temp = NULL;
	entry.cNum = 23;
	if (!elemNew(&entry))
		return 0;
	if (!elemGotoX(0, temp))
		return 0;
	elemPrint(temp);
	return 1;
}
void file_operater(char* path) {
	
	stopp_all_threads = 1;
	FILE* f;
	if ((f = fopen(path, "r+")) == NULL) {
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