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
    queue* prev;
}queue;

typedef struct map_data
{
    char map_data[5][4];
    map_data* next;
}map_data;
/* function in map.h */
bool check_complete();

void search_childs (node* parent);
bool create_node (node*  parent, char* dir);
void path_to_root (node);
void enqueue(node* now);
void dequeue();
void store_to_database(node* now)
bool search_database(node* now);
char transfer_map(char data);
long long node_count = 0; /*  node_count: record the total number of nodes, and it will be added by create_node. */

/*
char transfer_map(char data):
    this function will return transfer characters.
*/
char transfer_map(char data)
{
    switch(map[x][y])
    {
        case 0:
            return 0;
        case TT:
            return TT;
        case GY:
            return GY;
        case CF:
        case MC:
        case ZY:
        case HC:
            return CF;
        case Z:
        case P:
        case S:
        case H:
            return Z;
    }

}
/*
dequeue:
    dequeue a node and process it.
*/
void dequeue()
{
    if(!tail)
        printf("Dequeue error!!");
    else
    {
        search_child(tail);
        node* tmp = tail;
        if(tail->prev)
        {
            tail->prev->next = NULL;
            tail = tail->prev;
        }
        else
        {
            head = 0;
            free(tail);
            tail = 0;
        }
        free(tmp);
    }      
}
/*
enqueue:
    enqueue the node for BFS.
*/
void enqueue(node* now)
{
    if(!head && !tail) //first node
    {
        head = now;
        tail = now;
        now->next = 0;
        now->prev = 0;
        return;
    }
    else // Add to head
    {  
        now->next = head;
        now->prev = 0;
        head->prev = now;
        head = now;
        return;
    }
}
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
        if(!search_store_to_database(child))
        {
            enqueue(child);
            check_complete();
            return child;
        }   
    }
    free(child);
    return 0;
}
/*
char path_to_root(node):
   return a char array for finding the answer node.
 */
char* path_to_root(node);
/*
void store_to_database(node* now):
    This function store map[5][4] Info to database. If find return 1, else return 0.
*/
bool search_store_to_database(node* now)
{
    char parity = 0;
    map_data* new_data = (map_data *)malloc(sizeof(map_data));
    char i,j;
    map_data* tmp ;
    //transfer map to easy mode
    for(i=0; i<5; i++)
    {   
        for(j=0;j<4;j++)
        {
            new_data->map_data[i][j] = transfer_map(now->map[i][j]);
        }
    }
    //hash
    for(i=0; i<5; i++)
    {   
        for(j=0;j<4;j++)
        {   
            parity ^= new_data->map_data[i][j];
        }   
    }
    //find and store the node 
    tmp = database_arr[parity];
    
    while(tmp)
    {
        fail = 0;
        for(i=0; i<5; i++)
        {
            for(j=0;j<4;j++)
            {
                if(tmp->map_data[i][j] != new_data->map_data[i][j])
                {
                    i=5;
                    j=4;
                    fail = 1;
                }
            }
        }
        if(!fail)
        {
            free(new_data);
            return 1;
        }
        tmp = tmp->next;
    }
    //not found
    node_count++;
    new_data->next = database_arr[parity];
    database_arr[parity] = new_data;
    return 0;
}
queue* head,* tail;
map_data* database_arr[256] = {0};

int main()
{    
    // Set the BFS tree root
    node* root = (node *)malloc(sizeof(node)); /* node root:    root node(original map state). */
    root->parent = 0;
    root->visited = 0;
    init();
    int i, j;
    for(i=0; i<5; i++)
        for(j=0; j<4; j++)
            root->map[i][j] = map[i][j];
    queue* first_node = (queue *)malloc(sizeof(queue));
    first_node->now = root;
    enqueue(first_node);
    while(1)
    {
        dequeue();
    }
    return 0;
}
