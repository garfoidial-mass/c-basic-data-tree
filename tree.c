#include <stdio.h>
#include "tree.h"


int main()
{
    node_t* base = createnode("base");
    node_t *branch1;
    canode(&branch1,&base,"branch1");
    node_t *branch2;
    canode(&branch2,&base,"branch2");
    node_t *branch1of2;
    canode(&branch1of2,&branch2,"branch1of2");

    printtree(base);
    destroytree(base);
    printf("success");
    return 0;
}