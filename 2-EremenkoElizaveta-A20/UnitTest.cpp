#pragma once

#include "gtest/gtest.h"
extern "C" {
#include "Header.h"
}
TEST(Create_QueueTest, Check) {

	Queue* queue = NULL;
	queue = Create_Queue();
	EXPECT_TRUE(queue);
	EXPECT_TRUE(queue->first_ykazatel);
	EXPECT_FALSE(queue->first_ykazatel->data);
	EXPECT_FALSE(queue->first_ykazatel->priority);
	EXPECT_FALSE(queue->first_ykazatel->next);
	free(queue->first_ykazatel);
	free(queue);
}
TEST(Push_QueueTest, Add_Element_In_Push_Queue_Data_2_Pri_3) {
	Queue* queue = (Queue*)malloc(sizeof(Queue));
	if (!queue)
	{
		printf("Memory allocation error\n");
		exit(1);
	}
	queue->start = (List*)malloc(sizeof(List));
	if (!queue->start)
	{
		printf("Memory allocation error\n");
		free(queue);
		exit(1);
	}
	queue->start->data = 22;
	queue->start->priority = 2;
	queue->start->next = NULL;

	Push_Queue(queue, 11, 1);
	EXPECT_EQ(queue->start->data, 11);
	EXPECT_EQ(queue->start->priority, 1);
	EXPECT_EQ(queue->start->next->data, 22);
	EXPECT_EQ(queue->start->next->priority, 2);
	free(queue->start->next);
	free(queue->start);
	free(queue);
}
TEST(Push_QueueTest, Add_Element_In_Push_Queue_Data_2_Pri_3) {
	Queue* queue = (Queue*)malloc(sizeof(Queue));
	if (!queue)
	{
		printf("Memory allocation error\n");
		exit(1);
	}
	queue->start = (List*)malloc(sizeof(List));
	if (!queue->start)
	{
		printf("Memory allocation error\n");
		free(queue);
		exit(1);
	}
	queue->start->data = 0;
	queue->start->priority = 0;
	queue->start->next = NULL;

	Push_Queue(queue, 2, 3);
	EXPECT_EQ(queue->start->data, 2);
	EXPECT_EQ(queue->start->priority, 3);
	free(queue->start);
	free(queue);
}
TEST(Push_QueueTest, Add_Element_In_Push_Queue_And_Check_Order) {
	Queue* queue = (Queue*)malloc(sizeof(Queue));
	if (!queue)
	{
		printf("Memory allocation error\n");
		exit(1);
	}
	queue->start = (List*)malloc(sizeof(List));
	if (!queue->start)
	{
		printf("Memory allocation error\n");
		free(queue);
		exit(1);
	}
	queue->start->data = 0;
	queue->start->priority = 0;
	queue->start->next = NULL;

	Push_Queue(queue, 11, 1);
	Push_Queue(queue, 33, 3);
	Push_Queue(queue, 22, 2);
	EXPECT_EQ(queue->start->priority, 1);
	EXPECT_EQ(queue->start->data, 11);
	EXPECT_EQ(queue->start->next->priority, 2);
	EXPECT_EQ(queue->start->next->data, 22);
	EXPECT_EQ(queue->start->next->next->priority, 3);
	EXPECT_EQ(queue->start->next->next->data, 33);

	free(queue->start->next->next);
	free(queue->start->next);
	free(queue->start);
	free(queue);
}
TEST(Push_QueueTest, Add_Element_In_Push_Queue_And_Check_Order_With_Different_Input_Sequence) {
	Queue* queue = (Queue*)malloc(sizeof(Queue));
	if (!queue)
	{
		printf("Memory allocation error\n");
		exit(1);
	}
	queue->start = (List*)malloc(sizeof(List));
	if (!queue->start)
	{
		printf("Memory allocation error\n");
		free(queue);
		exit(1);
	}
	queue->start->data = 0;
	queue->start->priority = 0;
	queue->start->next = NULL;

	Push_Queue(queue, 22, 2);
	Push_Queue(queue, 11, 1);
	Push_Queue(queue, 33, 3);
	EXPECT_EQ(queue->start->priority, 1);
	EXPECT_EQ(queue->start->data, 11);
	EXPECT_EQ(queue->start->next->priority, 2);
	EXPECT_EQ(queue->start->next->data, 22);
	EXPECT_EQ(queue->start->next->next->priority, 3);
	EXPECT_EQ(queue->start->next->next->data, 33);

	free(queue->start->next->next);
	free(queue->start->next);
	free(queue->start);
	free(queue);
}
TEST(Push_QueueTest, Check_Input_Sequence_2) {
	Queue* queue = (Queue*)malloc(sizeof(Queue));
	if (!queue)
	{
		printf("Memory allocation error\n");
		exit(1);
	}
	queue->start = (List*)malloc(sizeof(List));
	if (!queue->start)
	{
		printf("Memory allocation error\n");
		free(queue);
		exit(1);
	}
	queue->start->data = 0;
	queue->start->priority = 0;
	queue->start->next = NULL;

	Push_Queue(queue, 22, 2);
	Push_Queue(queue, 11, 1);
	Push_Queue(queue, 33, 1);
	EXPECT_EQ(queue->start->priority, 1);
	EXPECT_EQ(queue->start->data, 11);
	EXPECT_EQ(queue->start->next->priority, 1);
	EXPECT_EQ(queue->start->next->data, 33);
	EXPECT_EQ(queue->start->next->next->priority, 2);
	EXPECT_EQ(queue->start->next->next->data, 22);

	free(queue->start->next->next);
	free(queue->start->next);
	free(queue->start);
	free(queue);
}
TEST(Pop_QueueTest, Create_Queue_And_Check_Pop) {
	int element = 0;
	Queue* queue = (Queue*)malloc(sizeof(Queue));
	if (!queue)
	{
		printf("Memory allocation error\n");
		exit(1);
	}
	queue->start = (List*)malloc(sizeof(List));
	if (!queue->start)
	{
		printf("Memory allocation error\n");
		free(queue);
		exit(1);
	}
	queue->start->data = 11;
	queue->start->priority = 1;
	queue->start->next = (List*)malloc(sizeof(List));
	if (!queue->start->next)
	{
		printf("Memory allocation error\n");
		free(queue);
		free(queue->start);
		exit(1);
	}
	queue->start->next->data = 22;
	queue->start->next->priority = 2;
	queue->start->next->next = NULL;

	element = Pop_Queue(queue);
	EXPECT_EQ(element, 11);
	element = Pop_Queue(queue);
	EXPECT_EQ(element, 22);
}
int main() {
	testing::InitGoogleTest();
	RUN_ALL_TESTS();
	return 0;
}