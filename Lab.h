#pragma once

typedef struct tree_t
{
    int s;
    int key[3];
    struct tree_t* one;
    struct tree_t* two;
    struct tree_t* three;
    struct tree_t* four;
    struct tree_t* parent;

} tree_t;

char Find_Value(int, int* , int );
void Swap(int* , int* );
void Sort_Two_Elements(int* , int* );
void Sort_Three_Elements(int* , int* , int* );
void Sort_Keys(int , int* );

tree_t* Create_Node(int );
tree_t* Create_Node_With_Sons(int , tree_t* , tree_t* , tree_t* , tree_t* , tree_t* );

void Add_Key(int , tree_t* );
void Remove_Key_Node(int , tree_t* );
void Become_Node(int , int*, tree_t* , tree_t* , tree_t* );

char Son(tree_t* );

tree_t* Split(tree_t* );
tree_t* AddNode(tree_t* , int );
tree_t* Search(tree_t* , int );
tree_t* FindMinimum(tree_t* );
tree_t* Merge(tree_t* );
tree_t* Redistribute(tree_t* );
tree_t* Fix(tree_t* );
tree_t* Remove_Node(tree_t* , int );

void Destroy_Tree(tree_t* );
void Print(tree_t* );