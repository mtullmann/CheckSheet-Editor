#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "utility.h"
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <stack> 
#include <iostream> 
using namespace std;

struct PROCESS_DATA {
	long int number = 0;
	string note = "";
	int charlength = 0;
	int cNum = 0;
	int cErrors=0;
	string cNames = "";
	FILE cStart;
	bool ok = 1;
}typedef PROCESS_DATA;

void file_operater(char* path);
bool elemExample();