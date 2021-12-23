//super simple generic data tree implementation
//modify to do whatever you want

#ifndef GENERIC_TREE
#define GENERIC_TREE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_t{
    char* name;
    int numchildren;
    struct node_t *parent;
    struct node_t **children;
}node_t;

node_t* createnode(char* name)
{
    node_t* node = malloc(sizeof(node_t));
    node->name = NULL;
    node->name = malloc(strlen(name)+1);
    strcpy(node->name,name);
    node->numchildren = 0;
    node->parent = NULL;
    return node;
}

int attachnode(node_t *node, node_t* parent)
{
    if(node->parent == NULL)
    {
        node->parent = parent;
        parent->numchildren += 1;
        if(parent->numchildren == 1)
        {
            parent->children = malloc(sizeof(node_t));
        }
        else if(parent->numchildren > 1)
        {
            parent->children = realloc(parent->children,sizeof(node_t)*parent->numchildren);
        }
        parent->children[parent->numchildren-1] = node;
    }
    else
    {
        return -1; //fail, you cannot attach already parented node, call detachnode first
    }
}

int canode(node_t **node, node_t **parent, char* name)
{
    *node = createnode(name);
    return attachnode(*node,*parent);
}

void destroynode(node_t* node)//really just resetting it, also call detachnode beforehand
{
    if(node->numchildren > 0)
    {
        free(node->children);
    }
    free(node->name);
    free(node);
}

int detachnode(node_t* node)
{
    if(node->parent != NULL)
    {
        int x = 0;
        while(x < node->parent->numchildren && node->parent->children[x-1] != node)
        {
            x++;
        }
        for(x = x; x < node->parent->numchildren; x++)
        {
            node->parent->children[x-1] = node->parent->children[x];
        }
        node->parent->numchildren--;
        node->parent->children = realloc(node->parent->children,sizeof(node_t)*node->parent->numchildren);
        node->parent = NULL;
    }
    else
    {
        return -1; // fail if node is unparented, what are we detaching it from?
    }
}

void ddnode(node_t *node)
{
    detachnode(node);
    destroynode(node);
}

void printtree(node_t *treebase)
{
    if(treebase->numchildren > 0)
    {
        printf("%s has %i children:\n", treebase->name, treebase->numchildren);
        for(int x = 0; x < treebase->numchildren; x++)
        {
            printf("%s\n",treebase->children[x]->name);
        }
        for(int x = 0; x < treebase->numchildren; x++)
        {
            printtree(treebase->children[x]);
        }
    }
    else
    {
        printf("%s has no children\n",treebase->name);
    }
}

void destroytree(node_t *treebase)
{
    int startnumchildren = treebase->numchildren;// copy of numchildren that doesn't get decremented as things are deleted
    for(int x = 0; x < startnumchildren; x++)
    {
        destroytree(treebase->children[0]);
    }
    printf("destroying %s\n",treebase->name);
    ddnode(treebase);
}
#endif