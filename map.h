char map[5][4];
typedef char bool;
/*
人名    代碼	大小	個數
-------------------------------
曹操:	TT	    2x2	    1
關羽:	GY	    1x2	    1
張飛:   CF	    2x1	    1
馬超:	MC	    2x1	    1
趙雲:	ZY	    2x1	    1
黃忠:	HC	    2x1	    1
卒:	    Z	    1x1	    4
*/
enum {Free, TT, GY, CF, MC, ZY, HC, Z};
enum {UP, RIGHT, DOWN, LEFT};
void init(void);
void push(char charac, int x, int y);
bool move(char dir);
void status(void);
void print_name(int x, int y);
int findfree();
bool checkcomplete(); 
//Initialize map to specific mode
//Set 0 to count
void init()
{
    int i, j;
    for (i=0; i<5; i++)
    {
        for (j=0; j<4; j++)
        {
            map[i][j] = 0;
        }
    }
    push(CF,0,0);
    push(TT,0,1);
    push(ZY,0,3);
    push(MC,2,0);
    push(GY,2,1);
    push(HC,2,3);
    push(Z,3,1);
    push(Z,3,2);
    push(Z,4,0);
    push(Z,4,3);
}
// push character into map[x][y]
void push(char charac, int x, int y)
{    
    switch(charac)
    {
        case 0:
            printf("error!! can't push free");
            break;
        case 1:
            if(x+1<5 && y+1<4 && !map[x][y] && !map[x+1][y] && !map[x][y+1] && !map[x+1][y+1])
            {
                map[x][y] = TT;
                map[x+1][y] = TT;
                map[x][y+1] = TT;
                map[x+1][y+1] = TT;
            }
            else
                printf("push TT error!!");    
            break;
        case 2:
            if(x<5 && y+1<4 && !map[x][y] && !map[x][y+1])
            {
                map[x][y] = GY;
                map[x][y+1] = GY;
            }
            else
                printf("push GY error!!");    
            break;
        case 3:
            if(x+1<5 && y<4 && !map[x][y] && !map[x+1][y])
            {
                map[x][y] = CF;
                map[x+1][y] = CF;
            }
            else
                printf("push CF error!!");   
            break;
        case 4:
            if(x+1<5 && y<4 && !map[x][y] && !map[x+1][y])
            {
                map[x][y] = MC;
                map[x+1][y] = MC;
            }
            else
                printf("push MC error!!");   
            break;
        case 5:
            if(x+1<5 && y<4 && !map[x][y] && !map[x+1][y])
            {
                map[x][y] = ZY;
                map[x+1][y] = ZY;
            }
            else
                printf("push ZY error!!");   
            break;
        case 6:
            if(x+1<5 && y<4 && !map[x][y] && !map[x+1][y])
            {
                map[x][y] = CF;
                map[x+1][y] = CF;
            }
            else
                printf("push HC error!!");   
            break;
        case 7:
            if(x<5 && y<4 && !map[x][y])
            {
                map[x][y] = Z;
            }
            else
                printf("push Z error!!");   
            break;
    }

}
//Move fuction
//Input:    UP, RIGHT, DOWN, LEFT
//Output:   0(fail), 1(success) 
bool move(char dir);
//See map status, and print out
void status()
{
    int i,j;
    for(i = 0; i<5; i++)
    {
        for(j=0; j<4; j++)
        {
            print_name(i,j);
        }
        printf("\n");
    }
}
//transfer and print number to people's name
void print_name(int x, int y)
{
    switch(map[x][y])
    {
        case 0:
            printf("   ");
            break;
        case 1:
            printf("TT ");
            break;
        case 2:
            printf("GY ");
            break;
        case 3:
            printf("CF ");
            break;
        case 4:
            printf("MC ");
            break;
        case 5:
            printf("ZY ");
            break;
        case 6:
            printf("HC ");
            break;
        case 7:
            printf("Z  ");
            break;
    }
}
//Find free blocks
//Output: two x-y coordinates
//        (32bit int 
//        0x X1X1 Y1Y1 X2X2 Y2Y2)
int findfree();
//Check map whether it's completed
bool checkcomplete();
