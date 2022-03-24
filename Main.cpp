#pragma warning(disable: 4996)
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "check.h"

#define TRUE 1
#define FALSE 0


int main() 
{
	Open_File(stdin);
	Solve();
	Answer(stdout);

	return 0;
}