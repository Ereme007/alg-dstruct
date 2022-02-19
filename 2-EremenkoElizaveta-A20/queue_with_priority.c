#include <stdio.h>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "Header.h"

Queue* Create_Queue()
{
	Queue* first_element_queue = (Queue*)malloc(sizeof(Queue));
	
	if (!first_element_queue)
	{
		printf("Error");
		exit(0);
	}
	
	first_element_queue->first_ykazatel = (List*)malloc(sizeof(List));

	if (!first_element_queue->first_ykazatel)
	{
		printf("Error");
		free(first_element_queue);
		exit(0);
	}

	first_element_queue->first_ykazatel->data = 0;
	first_element_queue->first_ykazatel->priority = 0;
	first_element_queue->first_ykazatel->next = NULL;

	return first_element_queue;
}


int Empty(Queue* queue)
{
	int a = 1;
	if (!queue)
	{
		a = 0;
		printf("Empty queue");
	}
	return a;
}


void Push_Queue(Queue* queue, int number, int priority)
{
	if (!queue)
	{
		printf("Error, empty: queue, number, priority");
		exit(1);
	}

	if (priority <= 0)
	{
		printf("Error");
		exit(0);
	}

	if (queue->first_ykazatel->priority == 0)
	{
		queue->first_ykazatel->data = number;
		queue->first_ykazatel->priority = priority;
		
		return queue;
	}

	List* new_element = (List*)malloc(sizeof(List));
	
	if (!new_element)
	{
		printf("Error");
		exit(0);
	}

	new_element->data = number;
	new_element->priority = priority;
	new_element->next = NULL;


	List* element1 = (List*)malloc(sizeof(List));
	List* element2 = (List*)malloc(sizeof(List));

	if ((!element1))
	{
		printf("Error");
		//free(element1); 
		//free(element2);
		exit(0);
	}

	if ((!element2))
	{
		printf("Error");
		free(element1);
		//free(element2);
		exit(0);
	}


	element1 = queue->first_ykazatel;
	element1->data = queue->first_ykazatel->data;
	element1->next = queue->first_ykazatel->next;
	element1->priority = queue->first_ykazatel->priority;
	element2 = queue->first_ykazatel->next;
	
	
	while (element1 != NULL)
	{
		//максимальный приоритет 1
		if (element2 != NULL)
		{
			if ((element2->priority) > (new_element->priority))
			{
				new_element->next = element1->next;
				element1->next = new_element;
				break;
			}
			else
			{
				if ((element2->next) == NULL)
				{
					new_element->next = element2->next;
					element2->next = new_element;
					break;
				}
			}

			element1 = element1->next;
			element2 = element2->next;
		}
		else
		{
			if ((element1->priority) > (new_element->priority))
			{
				new_element->next = element1;
				queue->first_ykazatel = new_element;
				break;
			}
			else
			{
				new_element->next = element1->next;
				element1->next = new_element;
				break;
			}
		}
	}
}


int Pop_Queue(Queue* queue)
{
	if (!queue)
	{
		printf("Error");
		exit(0);
	}

	int Ch = queue->first_ykazatel->data;
	queue->first_ykazatel = queue->first_ykazatel->next;
	return Ch;
}


void Delete_Queue(Queue* queue)
{
	List* new_element = queue->first_ykazatel;
	while (new_element != NULL)
	{
		List* tmp = new_element;
		new_element = new_element->next;
		free(tmp);
	}
	free(queue);
}
void Leak_Memory(void) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
}