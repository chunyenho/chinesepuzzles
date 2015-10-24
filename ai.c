/*
ai.c:
    This file can find a optimal way for solving the chinese puzzle by using
 some searching skills.
2015/10/23
*/
#include "map.h" 
typedef struct node 
{
    char map[5][4];
    node* parent;
    node* FU;
    node* FR;
    node* FD;
    node* FL;
    node* SU;
    node* SR;
    node* SD;
    node* SL;
}node;
/* function in map.h */
bool check_complete();

void search_childs (node* parent);
bool create_node (node*  parent, char dir);
void path_to_root (node);

long long node_count = 0; /*  node_count: record the number of nodes, and it will be added by create_node. */
node* root = (node *)malloc(sizeof(node)); /* node* root:    root node(original map state). */
/*
search_childs:
    This function call create_node 8 times for building childs. 
*/
void search_childs (node* parent);
/*
bool create_node():
    This function create a new node under a specific tree node by a specific direction, and set a new map state for the child.
 But the node may be invalidate or has been created. After setting, the function will return whether it is successful.
*/
bool create_node (node*  parent, char dir);
/*
char path_to_root(node):
    return a char array for finding the answer node.
*/
char* path_to_root (node);

