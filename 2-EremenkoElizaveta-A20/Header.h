#pragma once
#pragma warning(disable : 4996)
#ifdef __cplusplus

extern "C" {
#endif
	typedef struct List
	{
		int priority;
		int data;
		struct List* next;
	}List;

	typedef struct
	{
		List* first_ykazatel;
	}Queue;

	Queue* Create_Queue();
	void Push_Queue(Queue* queue, int number, int priority);
	void Delete_Queue(Queue* queue);
	int Empty(Queue* queue);
	int Pop_Queue(Queue* queue);
	void Leak_Memory(void);

#ifdef __cplusplus
}
#endif