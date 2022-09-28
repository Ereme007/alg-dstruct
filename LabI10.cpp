#include <stdio.h>
#include <stdlib.h>
#include "Lab.h"
#pragma warning(disable : 4996)
#pragma warning(disable : 6031)

tree_t* Create_Node(int value) 
{
    tree_t* New_Node = (tree_t*)malloc(sizeof(tree_t));

    if (New_Node) 
    {
        New_Node->one = NULL;
        New_Node->two = NULL;
        New_Node->three = NULL;
        New_Node->four = NULL;
        New_Node->parent = NULL;
        New_Node->key[0] = value;
        New_Node->s = 1;
    
        return New_Node;
    }

    return NULL;
}

tree_t* Create_Node_With_Sons(int value, tree_t* one, tree_t* two, tree_t* three, tree_t* four, tree_t* parent) 
{
    tree_t* New_Node = (tree_t*)malloc(sizeof(tree_t));

    if (New_Node) 
    {
        New_Node->one = one;
        New_Node->two = two;
        New_Node->three = three;
        New_Node->four = four;
        New_Node->parent = parent;
        New_Node->key[0] = value;
        New_Node->s = 1;
    
        return New_Node;
    }

    return NULL;
}

char Find_Value(int value, int* key, int s) 
{
    for (int i = 0; i < s; ++i) 
    {
        if (key[i] == value)
            return 1;
    }
    
    return 0;
}

tree_t* Search(tree_t* tree, int value) 
{
    if (tree == NULL)
        return NULL;

    if (Find_Value(value, tree->key, tree->s))
        return tree;

    else if (value < tree->key[0])
        return Search(tree->one, value);

    else if ((tree->s == 2) && (value < tree->key[1]) || (tree->s == 1))
        return Search(tree->two, value);

    else if (tree->s == 2)
        return Search(tree->three, value);
}

void Swap(int* x, int* y) 
{
    int r = (*x);
    (*x) = (*y);
    (*y) = r;
    //return x;
}

void Sort_Two_Elements(int* x, int* y) 
{
    if (*x > *y)
        Swap(x, y);
    //return x;
}

void Sort_Three_Elements(int* x, int* y, int* z)
{
    if (*x > *y)
        Swap(x, y);

    if (*x > *z)
        Swap(x, z);

    if (*y > *z)
        Swap(y, z);
}

void Sort_Keys(int count, int* key) 
{
    if (count == 1)
        return;

    if (count == 2)
        Sort_Two_Elements(&key[0], &key[1]);

    if (count == 3)
        Sort_Three_Elements(&key[0], &key[1], &key[2]);
}

void Add_Key(int value, tree_t* treeNode) 
{
    if (treeNode == NULL)
        return;

    treeNode->key[treeNode->s] = value;
    treeNode->s++;

    Sort_Keys(treeNode->s, treeNode->key);
}

void Remove_Key_Node(int value, tree_t* treeNode)
{
    if (treeNode == NULL)
        return;

    if (treeNode->s >= 1 && treeNode->key[0] == value) 
    {
        treeNode->key[0] = treeNode->key[1];
        treeNode->key[1] = treeNode->key[2];
        treeNode->s--;
    }
    
    else if (treeNode->s == 2 && treeNode->key[1] == value) 
    {
        treeNode->key[1] = treeNode->key[2];
        treeNode->s--;
    }
}

void Become_Node(int value, int* key, tree_t* treeNode, tree_t* one, tree_t* two) 
{
    key[0] = value;
    treeNode->one = one;
    treeNode->two = two;
    treeNode->three = NULL;
    treeNode->four = NULL;
    treeNode->parent = NULL;
    treeNode->s = 1;
}

char Son(tree_t* tree) 
{
    if (tree == NULL)
        return 0;

    if ((tree->one == NULL) && (tree->two == NULL) && (tree->three == NULL))
        return 1;

    return 0;
}

tree_t* Split(tree_t* item) 
{
    if (item == NULL)
        return NULL;

    if (item->s < 3)
        return item;

    tree_t* x = Create_Node_With_Sons(item->key[0], item->one, item->two, NULL, NULL, item->parent);
    tree_t* y = Create_Node_With_Sons(item->key[2], item->three, item->four, NULL, NULL, item->parent);

    if (x->one)
        x->one->parent = x;

    if (x->two) 
        x->two->parent = x;

    if (y->one)
        y->one->parent = y;

    if (y->two)
        y->two->parent = y;

    if (item->parent != NULL)
    {
        Add_Key(item->key[1], item->parent);

        if (item->parent->one == item)
            item->parent->one = NULL;

        else if (item->parent->two == item)
            item->parent->two = NULL;
        
        else if (item->parent->three == item)
            item->parent->three = NULL;

        if (item->parent->one == NULL) 
        {
            item->parent->four = item->parent->three;
            item->parent->three = item->parent->two;
            item->parent->two = y;
            item->parent->one = x;
        }
        
        else if (item->parent->two == NULL) 
        {
            item->parent->four = item->parent->three;
            item->parent->three = y;
            item->parent->two = x;
        }

        else 
        {
            item->parent->four = y;
            item->parent->three = x;
        }
        
        tree_t* tmp = item->parent;
        free(item);
        
        return tmp;
    }
    
    else 
    {
        x->parent = item;
        y->parent = item;
        Become_Node(item->key[1], item->key, item, x, y);
    
        return item;
    }
}

tree_t* AddNode(tree_t* tree, int value) 
{
    if (tree == NULL)
        return Create_Node(value);

    if (Search(tree, value))
        return Split(tree);

    if (Son(tree))
        Add_Key(value, tree);

    else if (value <= tree->key[0])
        AddNode(tree->one, value);

    else if ((tree->s == 1) || ((tree->s == 2) && value <= tree->key[1]))
        AddNode(tree->two, value);

    else
        AddNode(tree->three, value);

    return Split(tree);
}

tree_t* FindMinimum(tree_t* tree) 
{
    if (tree == NULL)
        return tree;

    if ((tree->one) == NULL)
        return tree;
    else
        return FindMinimum(tree->one);
}

tree_t* Redistribute(tree_t* node) 
{
    if (node == NULL)
        return NULL;

    tree_t* parent = node->parent;
    tree_t* first = parent->one;
    tree_t* second = parent->two;
    tree_t* third = parent->three;


    if ((parent->s == 2) && (first->s < 2) && (second->s < 2) && (third->s < 2)) 
    {
        if (first == node) 
        {
            parent->one = parent->two;
            parent->two = parent->three;
            parent->three = NULL;
            
            Add_Key(parent->key[0], parent->one);
            
            parent->one->three = parent->one->two;
            parent->one->two = parent->one->one;

            if (node->one != NULL)
                parent->one->one = node->one;
            
            else if (node->two != NULL)
                parent->one->one = node->two;

            if (parent->one->one != NULL)
                parent->one->one->parent = parent->one;

            Remove_Key_Node(parent->key[0], parent);
        }

        else if (second == node) 
        {
            Add_Key(parent->key[0], first);
            Remove_Key_Node(parent->key[0], parent);
        
            if (node->one != NULL)
                first->three = node->one;
            
            else if (node->two != NULL)
                first->three = node->two;

            if (first->three != NULL)
                first->three->parent = first;

            parent->two = parent->three;
            parent->three = NULL;

            free(second);
        }
        
        else if (third == node) 
        {
            Add_Key(parent->key[1], second);
            parent->three = NULL;
            Remove_Key_Node(parent->key[1], parent);
        
            if (node->one != NULL)
                second->three = node->one;
            
            else if (node->two != NULL)
                second->three = node->two;

            if (second->three != NULL)
                second->three->parent = second;

            free(third);
        }
    }
    else if ((parent->s == 2) && ((first->s == 2) || (second->s == 2) || (third->s == 2))) 
    {
        if (third == node) 
        {
            if (node->one != NULL) 
            {
                node->two = node->one;
                node->one = NULL;
            }

            Add_Key(parent->key[1], node);

            if (second->s == 2) 
            {
                parent->key[1] = second->key[1];
                Remove_Key_Node(second->key[1], second);
                node->one = second->three;
                second->three = NULL;

                if (node->one != NULL)
                    node->one->parent = node;
            }

            else if (first->s == 2)
            {
                parent->key[1] = second->key[0];
                node->one = second->two;
                second->two = second->one;
            
                if (node->one != NULL)
                    node->one->parent = node;

                second->key[0] = parent->key[0];
                parent->key[0] = first->key[1];
                Remove_Key_Node(first->key[1], first);
                second->one = first->three;
                
                if (second->one != NULL)
                    second->one->parent = second;

                first->three = NULL;
            }
        }
        else if (second == node) 
        {
            if (third->s == 2) 
            {
                if (node->one == NULL) 
                {
                    node->one = node->two;
                    node->two = NULL;
                }

                Add_Key(parent->key[1], second);
                parent->key[1] = third->key[0];
                
                Remove_Key_Node(third->key[0], third);
                second->two = third->one;
                
                if (second->two != NULL)
                    second->two->parent = second;

                third->one = third->two;
                third->two = third->three;
                third->three = NULL;
            }

            else if (first->s == 2) 
            {
                if (node->two == NULL)
                {
                    node->two = node->one;
                    node->one = NULL;
                }
                
                Add_Key(parent->key[0], second);
                parent->key[0] = first->key[1];
                
                Remove_Key_Node(first->key[1], first);
                second->one = first->three;
                
                if (second->one != NULL)
                    second->one->parent = second;

                first->three = NULL;
            }
        }
        
        else if (first == node) 
        {
            if (node->one == NULL) 
            {
                node->one = node->two;
                node->two = NULL;
            }

            Add_Key(parent->key[0], first);
            if (second->s == 2) 
            {
                parent->key[0] = second->key[0];
                Remove_Key_Node(second->key[0], second);
                first->two = second->one;
            
                if (first->two != NULL)
                    first->two->parent = first;

                second->one = second->two;
                second->two = second->three;
                second->three = NULL;
            }

            else if (third->s == 2) 
            {
                parent->key[0] = second->key[0];
                second->key[0] = parent->key[1];
                parent->key[1] = third->key[0];
                Remove_Key_Node(third->key[0], third);
                first->two = second->one;
            
                if (first->two != NULL)
                    first->two->parent = first;

                second->one = second->two;
                second->two = third->one;
                
                if (second->two != NULL)
                    second->two->parent = second;

                third->one = third->two;
                third->two = third->three;
                third->three = NULL;
            }
        }
    }

    else if (parent->s == 1) 
{
        Add_Key(parent->key[0], node);

        if (first == node && second->s == 2) 
        {
            parent->key[0] = second->key[0];
            Remove_Key_Node(second->key[0], second);

            if (node->one == NULL)
                node->one = node->two;

            node->two = second->one;
            second->one = second->two;
            second->two = second->three;
            second->three = NULL;
        
            if (node->two != NULL)
                node->two->parent = node;
        }
        else if (second == node && first->s == 2)
        {
            parent->key[0] = first->key[1];
            Remove_Key_Node(first->key[1], first);

            if (node->two == NULL)
                node->two = node->one;

            node->one = first->three;
            first->three = NULL;

            if (node->one != NULL)
                node->one->parent = node;
        }
    }
    return parent;
}

tree_t* Merge(tree_t* node) 
{
    if (node == NULL)
        return NULL;

    tree_t* parent = node->parent;

    if (parent->one == node) 
    {
        Add_Key(parent->key[0], parent->two);
        parent->two->three = parent->two->two;
        parent->two->two = parent->two->one;

        if (node->one != NULL)
            parent->two->one = node->one;
    
        else if (node->two != NULL)
            parent->two->one = node->two;

        if (parent->two->one != NULL)
            parent->two->one->parent = parent->two;

        Remove_Key_Node(parent->key[0], parent);
        
        free(parent->one);
        parent->one = NULL;
    }

    else if (parent->two == node) 
    {
        Add_Key(parent->key[0], parent->one);

        if (node->one != NULL)
            parent->one->three = node->one;
    
        else if (node->two != NULL)
            parent->one->three = node->two;

        if (parent->one->three != NULL)
            parent->one->three->parent = parent->one;

        Remove_Key_Node(parent->key[0], parent);
        
        free(parent->two);
        parent->two = NULL;
    }

    if (parent->parent == NULL) 
    {
        tree_t* tmp = NULL;
 
        if (parent->one != NULL)
            tmp = parent->one;
        else
            tmp = parent->two;

        tmp->parent = NULL;
        
        free(parent);
        return tmp;
    }

    return parent;
}


tree_t* Fix(tree_t* node)
{
    if (node == NULL)
        return NULL;

    if (node->s == 0 && node->parent == NULL) 
    {
        free(node);
       
        return NULL;
    }

    if (node->s != 0)
    {
        if (node->parent)
            return Fix(node->parent);
        
        else
            return node;
    }

    tree_t* parent = node->parent;

    if (parent->one->s == 2 || parent->two->s == 2 || parent->s == 2)
        node = Redistribute(node);
    
    else if (parent->s == 2 && parent->three->s == 2)
        node = Redistribute(node);
    
    else
        node = Merge(node);

    return Fix(node);
}


tree_t* Remove_Node(tree_t* tree, int value) 
{
    if (tree == NULL)
        return NULL;

    tree_t* item = Search(tree, value);

    if (item == NULL)
        return tree;

    tree_t* min = NULL;

    if (item->key[0] == value)
        min = FindMinimum(item->two);
    
    else
        min = FindMinimum(item->three);

    if (min != NULL) 
    {
        int* z = (value == item->key[0] ? &(item->key[0]) : &(item->key[1]));
        Swap(z, &min->key[0]);
        item = min;
    }

    Remove_Key_Node(value, item);
    
    return Fix(item);
}


void Print(tree_t* tree)
{
    if (tree == NULL)
        return;

    Print(tree->one);
   
    for (int i = 0; i < tree->s; i++)
        fprintf(stderr, "%d ", tree->key[i]);
   
    Print(tree->two);
    Print(tree->three);
}

void Destroy_Tree(tree_t* tree)
{
    if (tree == NULL)
        return;

    Destroy_Tree(tree->one);
    Destroy_Tree(tree->two);
    Destroy_Tree(tree->three);
    free(tree);
    //return tree;
}


int main( ) 
{

    char value;
    tree_t* prior = NULL;
    int key = 0;

    while (scanf("%c", &value) >= 1) 
    {
       //printf("Put symbol: ");
       if (value == 'a' || value == 'r' || value == 'f' )
            scanf("%i", &key);

        switch (value)
        {
        case 'a':
            prior = AddNode(prior, key);
            break;

        case 'r':
            prior = Remove_Node(prior, key);
            break;
        
        case 'f':
            if (Search(prior, key))
                puts("yes");
            else
                puts("no");
            break;

        case 'p':
            Print(prior);
            putchar('\n');
            break;

        case 'q':
            Destroy_Tree(prior);
            return 0;
            break;
        
        deafault:
            Destroy_Tree(prior);
            return 0;
            break;
        }
    }
}