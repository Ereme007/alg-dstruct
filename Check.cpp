#pragma warning(disable: 4996)
#include <stdlib.h>
#include "check.h"

#define TRUE 1
#define FALSE 0

int Number_Point, *Flag, **Graph, *Way, Number_1 = 0, Number_2= 0, Iter = 1; //Number_1, Number_2 - verteces of the Graph
char f = FALSE, Check_For_False;

static char Check(int Point)
{
	Flag[Point] = TRUE;
	Way[Iter - 1] = Point;

	if (Iter == Number_Point)
		return TRUE;

	for (int i = 0; i < Number_Point; i++) 
	{
		if (Graph[Point][i] && !Flag[i]) 
		{
			Iter++;
			Check_For_False = Check(i);
		}

		if (Check_For_False == FALSE)
		{
			if (i == Number_Point - 1) {
				Iter--;
				Flag[Point] = 0;
				
				return FALSE;
			}

		}
		else
			return TRUE;
	}

	return FALSE;
}

void Solve() 
{
	int Point_Count = 0;

	while (Point_Count < Number_Point && f == FALSE) 
	{
		if (Check(Point_Count))
		{
			f = TRUE;
			break;
		}
		else
			for (int i = 0; i < Number_Point; i++)
				Flag[i] = 0;

		Iter = 1;
		Point_Count++;
	}
}


void Open_File(FILE* Fp) 
{
	Fp = fopen("data.txt", "r");
	fscanf(Fp, "%d", &Number_Point);

	f = FALSE;

	Flag = (int*)calloc(Number_Point, sizeof(int));
	Graph = (int**)calloc(Number_Point, sizeof(int*));
	Way = (int*)calloc(Number_Point, sizeof(int));

	for (int i = 0; i < Number_Point; i++)
		Graph[i] = (int*)calloc(Number_Point, sizeof(int));

	while (fscanf(Fp, "%d %d", &Number_1, &Number_2) == 2)
		if (Fp == stdin && Number_1 == 0)
			break;
		else
			Graph[Number_1 - 1][Number_2 - 1] = Graph[Number_2 - 1][Number_1 - 1] = TRUE;
}

void Stress_Test() 
{
	Number_Point = TEST_POINT_NUMBER;

	Flag = (int*)calloc(Number_Point, sizeof(int));
	Graph = (int**)calloc(Number_Point, sizeof(int*));
	Way = (int*)calloc(Number_Point, sizeof(int));

	for (int i = 0; i < Number_Point; i++)
		Graph[i] = (int*)calloc(Number_Point, sizeof(int));

	for (int i = 0; i < TEST_POINT_NUMBER; i++)
		for (int Iter = i + 1; Iter < TEST_POINT_NUMBER; Iter++)
			if (rand() % 4 <= 3)
				Graph[i][Iter] = Graph[Iter][i] = 1;
}

void Answer(FILE* Fp) 
{
	if (f == TRUE && Number_Point != 0)
		for (int i = 0; i < Number_Point; i++)
			fprintf(Fp, "%d ", Way[i] + 1);
	else
		fprintf(Fp, "%d", 0);
}