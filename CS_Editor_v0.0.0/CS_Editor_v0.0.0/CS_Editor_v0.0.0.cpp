// CS_Editor_v0.0.0.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "utility.h"
#include "filedecoder.h"

char* fileName = NULL;
#define PROG_VERS "0.0.1"
#define PROG_TITLE1 "title CS Editor by Martin Tullmann Vers"
#define PROG_TITLE(a) strcpy(a,PROG_TITLE1);strcat(a,PROG_VERS);if(fileName!=NULL){strcat(a," \"");strcat(a,fileName);strcat(a,"\"");}
char* filePath = NULL;

void print_ProgTitle() {
	char a[801] = "";
	if (filePath != NULL) {
		char* x = NULL;
		int i = 0;
		for (i = strlen(filePath); filePath[i] != '\\' && i != -1; x = &filePath[i--]);
		fileName = x;
	}
	else
		fileName = NULL;
	PROG_TITLE(a);
	system(a);
}

int main(int argc, char* argv[])
{
	if (elemExample())
		printf("WORK!\n");
	bool allocatedMemory = 0;
	rcolor;
	print_ProgTitle();

	if (argc < 2) {
		printf("Type in your path of your ");
		color(GELBh);
		printf("checksheet\n");
		rcolor;
		if ((filePath = (char*)malloc(501)) == NULL) {
			printf("No Free RAM!!!\n\n");
			system("pause");
			exit(0);
		}
		getString(filePath, 501);
		allocatedMemory = 1;
		char* pnew = NULL;
		if ((pnew = (char*)malloc(strlen(filePath) + 1)) == NULL) {
			printf("No Free RAM!!!\n\n");
			system("pause");
			exit(0);
		}
		strcpy(pnew, filePath);
		free(filePath);
		filePath = pnew;
		printf("Path:%s\n", filePath);
	}
	else {
		filePath = argv[1];
	}
	print_ProgTitle();

	file_operater(filePath);
	printf("%i Bytes per check saved in RAM for faster executation!\n", (int)sizeof(PROCESS_DATA));
	system("pause");
	if (allocatedMemory)
		free(filePath);
	return 0;
}

