#include "LAB_H.h"
#include "main.c"

unsigned char height(node* point) 
{
    return point ? point->height : 0;
}

int bfactor(node* point) 
{
    return height(point->right) - height(point->left);
}

void fixheight(node* point) 
{
    unsigned char hl = height(point->left);
    unsigned char hr = height(point->right);
    point->height = (hl > hr ? hl : hr) + 1;
}

node* rotateright(node* point) 
{
    node* q = point->left;
    point->left = q->right;
    q->right = point;
    fixheight(point);
    fixheight(q);

    return q;
}

node* rotateleft(node* q) 
{
    node* point = q->right;
    q->right = point->left;
    point->left = q;
    fixheight(q);
    fixheight(point);

    return point;
}

node* balance(node* point) 
{
    fixheight(point);
    if (bfactor(point) == 2) 
    {
        if (bfactor(point->right) < 0)
            point->right = rotateright(point->right);

        return rotateleft(point);
    }
    if (bfactor(point) == -2)
    {
        if (bfactor(point->left) > 0)
            point->left = rotateleft(point->left);

        return rotateright(point);
    }
    return point;
}

node* insert(node* point, int k) 
{
    if (!point) 
    {
        point = (node*)malloc(sizeof(node));

        if (!point)
            return NULL;
        else 
        {
            point->key = k;
            point->left = NULL;
            point->right = NULL;
            point->height = 1;
            
            return point;
        }
    }

    if (k < point->key)
        point->left = insert(point->left, k);
    if (k > point->key)
        point->right = insert(point->right, k);
   
    return balance(point);
}

node* findmin(node* point) 
{
    return point->left ? findmin(point->left) : point;
}

node* removemin(node* point) 
{
    if (!point->left)
        return point->right;
    
    point->left = removemin(point->left);
   
    return balance(point);
}

node* delete(node* point, int k)
{
    if (!point)
        return 0;
   
    if (k < point->key)
        point->left = delete(point->left, k);
    else if (k > point->key)
        point->right = delete(point->right, k);
    else
    {
        node* q = point->left;
        node* r = point->right;
        free(point);
        if (!r)
            return q;
        node* min = findmin(r);
        min->right = removemin(r);
        min->left = q;
        
        return balance(min);
    }

    return balance(point);
}

void search(node* point, int k)
{
    if (!point)
    {
        fprintf(stdout, "no\n");
    
        return;
    }
    
    if (k == point->key)
    {
        fprintf(stdout, "yes\n");
    
        return;
    }
    
    if (k < point->key)
        search(point->left, k);
    else
        search(point->right, k);
}

void treedestroy(node* point)
{
    if (point)
    {
        treedestroy(point->left);
        treedestroy(point->right);
        free(point);
    }
}