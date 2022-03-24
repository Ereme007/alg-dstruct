#pragma warning(disable: 4996)
#include <stdlib.h>
#include <stdio.h>

typedef struct node_t 
{
    int number;
    struct node_t* node;
} node_t;

typedef struct 
{
    node_t* begin;
    node_t* end;
} list_t;

void freeList(list_t* list);
int readList(list_t lists[], int length);
int* DFS(list_t lists[], int length, int* lengthDFS);

int main() 
{
    list_t* lists;
    int n, i, lengthDFS;
    int error;
    int* dfs;
    
    if (scanf("%d", &n) < 0) 
    {
        printf("Error reading from stdin\n");
        return 1;
    }

    lists = (list_t*)malloc(sizeof(list_t) * n);
    
    if (!lists) 
        return 1;
 
    for (i = 0; i < n; i++) 
    {
        lists[i].begin = NULL;
        lists[i].end = NULL;
    }
    
    error = readList(lists, n);
    
    if (error == 1) 
    {
        free(lists);
        return 1;
    }

    dfs = DFS(lists, n, &lengthDFS);
    
    for (i = 0; i < lengthDFS; i++) 
        printf("%d ", dfs[i]);

    for (i = 0; i < n; i++) 
        freeList(&lists[i]);
    
    free(lists);
    
    return 0;
}

void freeList(list_t* list) 
{
    node_t* curElement = list->begin;

    while (curElement != NULL) 
    {
        list->begin = list->begin->node;
        free(curElement);
        curElement = list->begin;
    }
}

int readList(list_t lists[], int length) 
{
    int i, number;
    char ch;

    for (i = 0; i < length; i++) 
    {
        if (scanf("%d%c", &number, &ch) < 0)
            return 1;

        while (ch == ' ') 
        {
            if (scanf("%d%c", &number, &ch) < 0) 
                return 1;

            if (!lists[i].begin) 
            {
                lists[i].begin = (node_t*)malloc(sizeof(node_t));
                
                if (lists[i].begin == NULL) 
                {
                    for (i = 0; i < length; i++) 
                        freeList(&lists[i]);

                    return 1;
                }

                lists[i].end = lists[i].begin;
            }

            else 
            {
                lists[i].end->node = (node_t*)malloc(sizeof(node_t));
                
                if (lists[i].end->node == NULL) 
                {
                    for (i = 0; i < length; i++)
                        freeList(&lists[i]);
                    
                    return 1;
                }

                lists[i].end = lists[i].end->node;
            }

            lists[i].end->number = number;
            lists[i].end->node = NULL;
            
            if (i < number) 
            {
                if (!lists[number].begin) 
                {
                    lists[number].begin = (node_t*)malloc(sizeof(node_t));
                    
                    if (lists[number].begin == NULL) 
                    {
                        for (i = 0; i < length; i++) 
                            freeList(&lists[i]);

                        return 1;
                    }
                    lists[number].end = lists[number].begin;
                }
                else 
                {
                    lists[number].end->node = (node_t*)malloc(sizeof(node_t));

                    if (lists[number].end->node == NULL)
                    {
                        for (i = 0; i < length; i++) 
                            freeList(&lists[i]);
                        
                        return 1;
                    }

                    lists[number].end = lists[number].end->node;
                }

                lists[number].end->number = i;
                lists[number].end->node = NULL;
            }
        }
    }
    return 0;
}

int* DFS(list_t lists[], int length, int* lengthDFS)
{
    int* dfs = (int*)malloc(sizeof(int) * length);

    struct 
    {
        int* elements;
        int  topOfStack;
    } stack;
    
    int i = 0, j;
    node_t* curNode;
    stack.elements = (int*)malloc(sizeof(int) * length);

    if (!dfs || !stack.elements) 
    {
        free(dfs);
        free(stack.elements);
    
        return 0;
    }

    dfs[0] = 0;
    *lengthDFS = 1;
    stack.elements[0] = 0;
    stack.topOfStack = 0;

    while (stack.topOfStack != -1) 
    {
        curNode = lists[i].begin;
        for (j = 0; j < *lengthDFS; j++) 
        {
            if (curNode != NULL && curNode->number == dfs[j]) 
            {
                curNode = curNode->node;
                j = 0;
            }
        }

        if (curNode == NULL) 
        {
            i = stack.elements[stack.topOfStack - 1];
            stack.topOfStack--;
        }
        else 
        {
            stack.topOfStack++;
            stack.elements[stack.topOfStack] = curNode->number;
            
            (*lengthDFS)++;
            dfs[*lengthDFS - 1] = curNode->number;
            
            i = curNode->number;
        }
    }

    return dfs;
}