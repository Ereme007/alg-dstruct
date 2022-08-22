#pragma once
#pragma warning(disable: 4996)
#include "AVL.c"
#include "main.c"

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int key;
    unsigned char height;
    struct node* left;
    struct node* right;
} node;

unsigned char height(node* point);
int bfactor(node* point);
void fixheight(node* point);

node* rotateright(node* point);
node* rotateleft(node* q);
node* balance(node* point);
node* insert(node* point, int k);
node* findmin(node* point);
node* removemin(node* point);
node* delete(node* point, int k);

void search(node* point, int k);
void treedestroy(node* point);