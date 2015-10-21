char map[5][4];
typedef char bool;
int steps = 0;
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
void pull(char charac);
void push(char charac, int x, int y);
bool move(char* dir);
void status(void);
void print_name(int x, int y);
int find_free();
int find_charac(char charac, int* x, int* y);
bool can_move(char charac, char dir, int x, int y);
bool check_complete(); 
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
// pull character out from map
void pull(char charac)
{
    int i, j;
    for (i=0; i<5; i++)
    {
        for (j=0; j<4; j++)
        {
            if(map[i][j] == charac)
            {
                map[i][j] = 0;
            }
        }
    }
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
//Input:    FU(First Up), FR, FD, FL, SU(Second Up), SR, SD, SL
//Output:   0(fail), 1(success) 
bool move(char* dir);
{
    char succ = 0;
    int fir_x, fir_y, sec_x, sec_y, tmp, tmp_x, tmp_y;
    tmp = findfree();
    fir_x = (tmp>>24) & 0xff;
    fir_y = (tmp>>16) & 0xff;
    sec_x = (tmp>>8 ) & 0xff;
    sec_y =  tmp      & 0xff;
    if(dir[0]=='F')
    {
        switch(dir[1])
        {
            case 'U':
                if(map[fir_x][fir_y+1])
                {
                    tmp = map[fir_x][fir_y+1]; //tmp record the character
                    find_charac((char)tmp,&tmp_x,&tmp_y);
                    if(can_move((char)tmp,U,tmp_x,tmp_y))
                    {
                        steps++;
                        pull((char)tmp);
                        push((char)tmp,tmp_x,tmp_y-1);
                    }    
                }
                break;
            case 'R':
                if(map[fir_x-1][fir_y])
                {
                    tmp = map[fir_x-1][fir_y]; //tmp record the character
                    find_charac((char)tmp,&tmp_x,&tmp_y);
                    if(can_move((char)tmp,R,tmp_x,tmp_y))
                    {
                        steps++;
                        pull((char)tmp);
                        push((char)tmp,tmp_x+1,tmp_y);
                    }    
                }
                break;
            case 'D':
                if(map[fir_x][fir_y-1])
                {
                    tmp = map[fir_x][fir_y-1]; //tmp record the character
                    find_charac((char)tmp,&tmp_x,&tmp_y);
                    if(can_move((char)tmp,D,tmp_x,tmp_y))
                    {
                        steps++;
                        pull((char)tmp);
                        push((char)tmp,tmp_x,tmp_y+1);
                    }    
                }
                break;
            case 'L':
                if(map[fir_x+1][fir_y])
                {
                    tmp = map[fir_x+1][fir_y]; //tmp record the character
                    find_charac((char)tmp,&tmp_x,&tmp_y);
                    if(can_move((char)tmp,L,tmp_x,tmp_y))
                    {
                        steps++;
                        pull((char)tmp);
                        push((char)tmp,tmp_x-1,tmp_y);
                    }    
                }
                break;
        }
    }
    if(dir[0]=='S')
    {
        switch(dir[1])
        {
            case 'U':
                if(map[sec_x][sec_y+1])
                {
                    tmp = map[sec_x][sec_y+1]; //tmp record the character
                    find_charac((char)tmp,&tmp_x,&tmp_y);
                    if(can_move((char)tmp,U,tmp_x,tmp_y))
                    {
                        steps++;
                        pull((char)tmp);
                        push((char)tmp,tmp_x,tmp_y-1);
                    }    
                }
                break;
            case 'R':
                if(map[sec_x-1][sec_y])
                {
                    tmp = map[sec_x-1][sec_y]; //tmp record the character
                    find_charac((char)tmp,&tmp_x,&tmp_y);
                    if(can_move((char)tmp,R,tmp_x,tmp_y))
                    {
                        steps++;
                        pull((char)tmp);
                        push((char)tmp,tmp_x+1,tmp_y);
                    }    
                }
                break;
            case 'D':
                if(map[sec_x][sec_y-1])
                {
                    tmp = map[sec_x][sec_y-1]; //tmp record the character
                    find_charac((char)tmp,&tmp_x,&tmp_y);
                    if(can_move((char)tmp,D,tmp_x,tmp_y))
                    {
                        steps++;
                        pull((char)tmp);
                        push((char)tmp,tmp_x,tmp_y+1);
                    }    
                }
                break;
            case 'L':
                if(map[sec_x+1][sec_y])
                {
                    tmp = map[sec_x+1][sec_y]; //tmp record the character
                    find_charac((char)tmp,&tmp_x,&tmp_y);
                    if(can_move((char)tmp,L,tmp_x,tmp_y))
                    {
                        steps++;
                        pull((char)tmp);
                        push((char)tmp,tmp_x-1,tmp_y);
                    }    
                }
                break;
        }
    }
}

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
int find_free()
{
    int count = 0, result = 0;
    for(i=0; i<5; i++)
    {
        for(j=0; j<4; j++)
        {
            if(map[i][j] == 0)
            { 
                count ++;
                result <<= 8;
                result += i;
                result <<= 8;
                result += j;
            } 
        }
    }
}
//Check map whether it's completed
bool check_complete()
{
    if(map[3][1]==TT && map[3][2]==TT && map[4][1]==TT && map[4][2]==TT)
    {
        printf("Success!!!!!!!!!");
        break; 
    }
}
