#include <stdio.h>
#include "memallocator.h"

void* g_head = NULL;
void* Top_Heap = NULL;
void* next_good = NULL;
int s_size = 0;

int memgetminimumsize()
{
    return sizeof(int) + sizeof(void*) + sizeof(void*) + sizeof(int);
}

int memgetblocksize() 
{
    return sizeof(int) + sizeof(void*) + sizeof(void*) + sizeof(int);
}


int* Left_Size_Block(void* block) 
{
    return (int*)block;
}

void** Next_Block(void* block) 
{
    return (void**)((char*)block + sizeof(int));
}

void** Prev_Block(void* block) 
{
    return (void**)((char*)block + sizeof(int) + sizeof(void*));
}

int* Right_Size_Block(void* block) 
{
    return (int*)((char*)block + *Left_Size_Block(block) - sizeof(int));
}

int meminit(void* pMemory, int size) 
{
    if (size <= memgetminimumsize())
        return 0;

    void* block = pMemory;

    *Left_Size_Block(block) = size;
    *Next_Block(block) = NULL;
    *Prev_Block(block) = NULL;
    *Right_Size_Block(block) = size;

    g_head = block;
    Top_Heap = pMemory;
    s_size = size;
    next_good = g_head;

    return size;
}

void memdone() 
{
    void* block = Top_Heap;
    while ((char*)block < (char*)Top_Heap + s_size) {
        if (*Right_Size_Block(block) < 0)
            fprintf(stderr, "[MEMORY LEAK] block at 0x%p\n", (char*)block + sizeof(int) + sizeof(void*) + sizeof(void*));
        block = (void*)((char*)block + *Left_Size_Block(block));
    }
}

void* memalloc(int size) 
{
    if (size < 1 || size > s_size - memgetblocksize())
        return NULL;
    
    void* suitBlock = next_good;
    int found = 0;
    void* freeBlock = NULL;
    void* prev = NULL;
    
    while (found != 1 && suitBlock != NULL) 
    {
        if (*Left_Size_Block(suitBlock) >= memgetblocksize() + size) 
            found = 1;
       
        prev = suitBlock;
        suitBlock = *Next_Block(suitBlock);

        if (found == 0 && next_good != g_head && suitBlock == NULL)
            suitBlock = g_head;
        if (suitBlock == next_good)
            break;
    }

    if (found == 0) 
        return NULL;

    suitBlock = prev;
    
    if (*Left_Size_Block(suitBlock) > memgetblocksize() + size + memgetblocksize()) 
    {
        freeBlock = (void*)((char*)suitBlock + memgetblocksize() + size);
        *Left_Size_Block(freeBlock) = *Left_Size_Block(suitBlock) - memgetblocksize() - size;
        *Next_Block(freeBlock) = *Next_Block(suitBlock);
        *Prev_Block(freeBlock) = *Prev_Block(suitBlock);
        *Right_Size_Block(freeBlock) = *Left_Size_Block(freeBlock);
        
        if (*Prev_Block(suitBlock) != NULL)
            *Next_Block(*Prev_Block(suitBlock)) = freeBlock;
        else
            g_head = freeBlock;
        if (*Next_Block(suitBlock) != NULL)
            *Prev_Block(*Next_Block(suitBlock)) = freeBlock;
        
        *Left_Size_Block(suitBlock) = memgetblocksize() + size;
    }
    else 
    {
        if (*Prev_Block(suitBlock) != NULL) 
        {
            *Next_Block(*Prev_Block(suitBlock)) = *Next_Block(suitBlock);
            
            if (*Next_Block(suitBlock) != NULL)
                *Prev_Block(*Next_Block(suitBlock)) = *Prev_Block(suitBlock);
        }
        else 
        {
            g_head = *Next_Block(suitBlock);
            
            if (g_head != NULL)
                *Prev_Block(g_head) = NULL;
        }
    }

    if (*Next_Block(suitBlock) != NULL)
        next_good = *Next_Block(suitBlock);

    else
        next_good = g_head;

    *Right_Size_Block(suitBlock) = -*Left_Size_Block(suitBlock);
    *Next_Block(suitBlock) = NULL;
    *Prev_Block(suitBlock) = NULL;
    return (void*)((char*)suitBlock + sizeof(int) + sizeof(void*) + sizeof(void*));
}

// Free memory previously allocated by memalloc
void memfree(void* p) 
{
    void* free_future = (void*)((char*)p - sizeof(void*) - sizeof(int) - sizeof(void*));
    void* left_block = NULL;
    void* right_block = NULL;
    int united_left = 0;
    int united_right = 0;

    if (((char*)free_future - 1) > (char*)Top_Heap)
        left_block = (void*)((char*)free_future - (*((int*)free_future - 1) >= 0 ? *((int*)free_future - 1) : -*((int*)free_future - 1)));

    if ((char*)free_future + *Left_Size_Block(free_future) + 1 < (char*)Top_Heap + s_size)
        right_block = (void*)(Right_Size_Block(free_future) + 1);

    *Right_Size_Block(free_future) = -*Right_Size_Block(free_future);
    
    if (left_block != NULL && *Right_Size_Block(left_block) > 0) 
    {
        united_left = 1;
        
        *Left_Size_Block(left_block) = *Left_Size_Block(left_block)  + *Left_Size_Block(free_future);
        *Right_Size_Block(left_block) = *Left_Size_Block(left_block);
        
        free_future = left_block;
    }

    if (right_block != NULL && *Right_Size_Block(right_block) > 0) 
    {
        united_right = 1;
        
        if (united_left == 0) 
        {
            *Next_Block(free_future) = g_head;
            *Prev_Block(g_head) = free_future;
            *Prev_Block(free_future) = NULL;
            g_head = free_future;
        }
 
        if (right_block == g_head) 
        {
            g_head = *Next_Block(right_block);
            *Prev_Block(g_head) = NULL;
        }
        else 
        {
            *Next_Block(*Prev_Block(right_block)) = *Next_Block(right_block);

            if (*Next_Block(right_block) != NULL)
                *Prev_Block(*Next_Block(right_block)) = *Prev_Block(right_block);
        }

        *Left_Size_Block(free_future) = *Left_Size_Block(free_future) + *Left_Size_Block(right_block);
        *Right_Size_Block(free_future) = *Left_Size_Block(free_future);

        if (next_good == right_block)
            next_good = free_future;
    }

    if (united_left == 0 && united_right == 0) 
    {
        *Next_Block(free_future) = g_head;
        if (g_head != NULL)
            *Prev_Block(g_head) = free_future;
        else
            next_good = free_future;

        *Prev_Block(free_future) = NULL;
        g_head = free_future;
    }
}