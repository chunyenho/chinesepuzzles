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
    bool visited;
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

typedef struct queue
{
    node* now;
    queue* next;
    queue* pre;
}
/* function in map.h */
bool check_complete();

void search_childs (node* parent);
bool create_node (node*  parent, char* dir);
void path_to_root (node);
void enqueue_node(node* now);
node* dequeue_parent();

long long node_count = 0; /*  node_count: record the total number of nodes, and it will be added by create_node. */
node* root = (node *)malloc(sizeof(node)); /* node* root:    root node(original map state). */
/*
search_childs:
    This function call create_node 8 times for building childs. 
 */
void search_childs (node* parent)
{
    if(!parent->visited)
    {
        parent->FU = create_node(parent, "FU");
        parent->FR = create_node(parent, "FR");
        parent->FD = create_node(parent, "FD"); 
        parent->FL = create_node(parent, "FL");
        parent->SU = create_node(parent, "SU");
        parent->SR = create_node(parent, "SR");
        parent->SD = create_node(parent, "SD");
        parent->SL = create_node(parent, "SL");
        parent->visited = 1;
    }
    else
        printf("node visited error!!");
}
/*
bool create_node():
   This function create a new node under a specific tree node by a specific direction, and set a new map state for the child.
   But the node may be invalidate or has been created. After setting, the function will return whether it is successful.
 */
node* create_node (node*  parent, char* dir)
{
    int i,j;
    for(i=0; i<5; i++)
    {
        for(j=0;j<4;j++)
        {
            map[i][j] = parent->map[i][j];
        }
    }
    node* child = (node*)malloc(sizeof(node));
    if(move(dir))
    {
       for(i=0; i<5; i++)
      {   
          for(j=0;j<4;j++)
          {   
              child->map[i][j] = map[i][j];
          }   
      }
      if(!search_database(child))
      {
          enqueue(child);
          check_complete();
      }   
    }
    free(child);
}
/*
char path_to_root(node):
   return a char array for finding the answer node.
 */
char* path_to_root (node);

int main()
{
        
}
