#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "utility.h"
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <stack> 

struct PROCESS_DATA {
	FILE* startPoint = NULL;
	long int number = 0;
	char* note = NULL;
	int cNum = 0;
	int* cErrors = NULL;
	char* cNames = NULL;
	FILE* cStart=NULL;
	bool ok = 1;
	PROCESS_DATA* pNext = NULL;
}typedef PROCESS_DATA;

void file_operater(char* path);
bool elemExample();