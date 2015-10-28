/*
map.h:
    Define map, characters, operation functions in the game.
*/
/*
人名    代碼	大小	個數
-------------------------------
曹操:	TT	    2x2	    1
關羽:	GY	    1x2	    1
張飛:   CF	    2x1	    1
馬超:	MC	    2x1	    1
趙雲:	ZY	    2x1	    1
黃忠:	HC	    2x1	    1
卒:	    Z	    1x1	    1
兵:     P       1x1     1
象:     S       1x1     1
士:     H       1x1     1
*/
char map[5][4];
typedef char bool;
int steps = 0;
enum {Free, TT, GY, CF, MC, ZY, HC, Z, P, S, H};
enum {UP, RIGHT, DOWN, LEFT};
void init(void);
void pull(char charac);
void push(char charac, int x, int y);
bool move(char* dir);
void status(void);
void print_name(int x, int y);
int find_free();
void find_charac(char charac, int* x, int* y);
bool can_move(char charac, char dir, int x, int y); // <-----
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
    push(P,3,2);
    push(S,4,0);
    push(H,4,3);
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
        case Free:
            printf("error!! can't push free");
            break;
        case TT:
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
        case GY:
            if(x<5 && y+1<4 && !map[x][y] && !map[x][y+1])
            {
                map[x][y] = GY;
                map[x][y+1] = GY;
            }
            else
                printf("push GY error!!");    
            break;
        case CF:
            if(x+1<5 && y<4 && !map[x][y] && !map[x+1][y])
            {
                map[x][y] = CF;
                map[x+1][y] = CF;
            }
            else
                printf("push CF error!!");   
            break;
        case MC:
            if(x+1<5 && y<4 && !map[x][y] && !map[x+1][y])
            {
                map[x][y] = MC;
                map[x+1][y] = MC;
            }
            else
                printf("push MC error!!");   
            break;
        case ZY:
            if(x+1<5 && y<4 && !map[x][y] && !map[x+1][y])
            {
                map[x][y] = ZY;
                map[x+1][y] = ZY;
            }
            else
                printf("push ZY error!!");   
            break;
        case HC:
            if(x+1<5 && y<4 && !map[x][y] && !map[x+1][y])
            {
                map[x][y] = HC;
                map[x+1][y] = HC;
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
        case P:
            if(x<5 && y<4 && !map[x][y])
              {   
                  map[x][y] = P;
              }   
              else
                  printf("push P error!!");   
              break;
        case S:
            if(x<5 && y<4 && !map[x][y])
              {   
                  map[x][y] = S;
              }   
              else
                  printf("push S error!!");   
              break;
        case H:
            if(x<5 && y<4 && !map[x][y])
              {   
                  map[x][y] = H;
              }   
              else
                  printf("push H error!!");   
              break;

    }

}
//Move fuction
//Input:    FU(First Up), FR, FD, FL, SU(Second Up), SR, SD, SL
//Output:   0(fail), 1(success) 
bool move(char* dir)
{
    char succ = 0;
    int fir_x, fir_y, sec_x, sec_y, tmp, tmp_x, tmp_y;
    tmp = find_free();
    fir_x = (tmp>>24) & 0xff;
    fir_y = (tmp>>16) & 0xff;
    sec_x = (tmp>>8 ) & 0xff;
    sec_y =  tmp      & 0xff;
    if(dir[0]=='F')
    {
        switch(dir[1])
        {
            case 'U':
                if(map[fir_x+1][fir_y])
                {
                    tmp = map[fir_x+1][fir_y]; //tmp record the character
                    find_charac((char)tmp,&tmp_x,&tmp_y);
                    if(can_move((char)tmp,'U',tmp_x,tmp_y))
                    {
                        steps++;
                        pull((char)tmp);
                        push((char)tmp,tmp_x-1,tmp_y);
                        return 1;
                    }
                    else
                    {
                        printf("Can't push!!\n");
                        return 0;
                    }    
                }
                break;
            case 'R':
                if(map[fir_x][fir_y-1])
                {
                    tmp = map[fir_x][fir_y-1]; //tmp record the character
                    find_charac((char)tmp,&tmp_x,&tmp_y);
                    if(can_move((char)tmp,'R',tmp_x,tmp_y))
                    {
                        steps++;
                        pull((char)tmp);
                        push((char)tmp,tmp_x,tmp_y+1);
                        return 1;
                    }
                    else
                    {
                        printf("Can't push!!\n");
                        return 0;
                    }     
                }
                break;
            case 'D':
                if(map[fir_x-1][fir_y])
                {
                    tmp = map[fir_x-1][fir_y]; //tmp record the character
                    find_charac((char)tmp,&tmp_x,&tmp_y);
                    if(can_move((char)tmp,'D',tmp_x,tmp_y))
                    {
                        steps++;
                        pull((char)tmp);
                        push((char)tmp,tmp_x+1,tmp_y);
                        return 1;
                    } 
                    else
                    {
                        printf("Can't push!!\n");
                        return 0;
                    }    
                }
                break;
            case 'L':
                if(map[fir_x][fir_y+1])
                {
                    tmp = map[fir_x][fir_y+1]; //tmp record the character
                    find_charac((char)tmp,&tmp_x,&tmp_y);
                    if(can_move((char)tmp,'L',tmp_x,tmp_y))
                    {
                        steps++;
                        pull((char)tmp);
                        push((char)tmp,tmp_x,tmp_y-1);
                        return 1;
                    } 
                    else
                    {
                        printf("Can't push!!\n");
                        return 0;
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
                if(map[sec_x+1][sec_y])
                {
                    tmp = map[sec_x+1][sec_y]; //tmp record the character
                    find_charac((char)tmp,&tmp_x,&tmp_y);
                    if(can_move((char)tmp,'U',tmp_x,tmp_y))
                    {
                        steps++;
                        pull((char)tmp);
                        push((char)tmp,tmp_x-1,tmp_y);
                        return 1;
                    } 
                    else
                    {
                        printf("Can't push!!\n");
                        return 0;
                    }    
                }
                break;
            case 'R':
                if(map[sec_x][sec_y-1])
                {
                    tmp = map[sec_x][sec_y-1]; //tmp record the character
                    find_charac((char)tmp,&tmp_x,&tmp_y);
                    if(can_move((char)tmp,'R',tmp_x,tmp_y))
                    {
                        steps++;
                        pull((char)tmp);
                        push((char)tmp,tmp_x,tmp_y+1);
                        return 1;
                    } 
                    else
                    {
                        printf("Can't push!!\n");
                        return 0;
                    }    
                }
                break;
            case 'D':
                if(map[sec_x-1][sec_y])
                {
                    tmp = map[sec_x-1][sec_y]; //tmp record the character
                    find_charac((char)tmp,&tmp_x,&tmp_y);
                    if(can_move((char)tmp,'D',tmp_x,tmp_y))
                    {
                        steps++;
                        pull((char)tmp);
                        push((char)tmp,tmp_x+1,tmp_y);
                        return 1;
                    }  
                    else
                    {
                        printf("Can't push!!\n");
                        return 0;
                    }   
                }
                break;
            case 'L':
                if(map[sec_x][sec_y+1])
                {
                    tmp = map[sec_x][sec_y+1]; //tmp record the character
                    find_charac((char)tmp,&tmp_x,&tmp_y);
                    if(can_move((char)tmp,'L',tmp_x,tmp_y))
                    {
                        steps++;
                        pull((char)tmp);
                        push((char)tmp,tmp_x,tmp_y-1);
                        return 1;
                    }  
                    else
                    {
                        printf("Can't push!!\n");
                        return 0;
                    }  
                }
                break;
        }
    }
    return -1;
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
        case TT:
            printf("TT ");
            break;
        case GY:
            printf("GY ");
            break;
        case CF:
            printf("CF ");
            break;
        case MC:
            printf("MC ");
            break;
        case ZY:
            printf("ZY ");
            break;
        case HC:
            printf("HC ");
            break;
        case Z:
            printf("Z  ");
            break;
        case P:
            printf("P  ");
            break;
        case S:
            printf("S  ");
            break;
        case H:
            printf("H  ");
            break;
    }
}
//Find free blocks
//Output: two x-y coordinates
//        (32bit int 
//        0x X1X1 Y1Y1 X2X2 Y2Y2)
int find_free()
{
    int i, j;
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
    return result;
}
//find the up-left corner of the character
void find_charac(char charac, int* x, int* y)
{
    int i, j;
    for(i=0;i<5;i++)
    {
        for(j=0;j<4;j++)
        {
            if(map[i][j] == charac)
            {
                *x= i;
                *y= j;
                return;
            }
        }
    }
}
bool can_move(char charac, char dir, int x, int y)
{
    switch(charac)
    {
        case Free:
            printf("can't move free!");
            break;
        case TT:
            switch(dir)
            {
                case 'U':
                    if(!map[x-1][y] && !map[x-1][y+1])
                        return 1;
                    else
                        return 0;
                    break;
                case 'R':
                    if(!map[x][y+2] && !map[x+1][y+2])
                        return 1;
                    else  
                        return 0;
                    break;
                case 'D':
                    if(!map[x+2][y] && !map[x+2][y+1])
                        return 1;
                    else  
                        return 0;
                    break;
                case 'L':
                    if(!map[x][y-1] && !map[x+1][y-1])
                        return 1;
                    else  
                        return 0;
                    break;
            }
            break;
        case GY:
            switch(dir)
            {
                case 'U':
                    if(!map[x-1][y] && !map[x-1][y+1])
                        return 1;
                    else
                        return 0;
                    break;
                case 'R':
                    if(!map[x][y+2])
                        return 1;
                    else
                        return 0;
                    break;
                case 'D':
                    if(!map[x+1][y] && !map[x+1][y+1])
                        return 1;
                    else 
                        return 0;
                    break;
                case 'L':
                    if(!map[x][y-1])
                        return 1;
                    else
                        return 0;
                    break;
            }
            break;
        case MC:
        case CF:
        case ZY:
        case HC:
            switch(dir)
            {
                case 'U': 
                    if(!map[x-1][y])
                        return 1;
                    else   
                        return 0;
                    break;
                case 'R': 
                    if(!map[x][y+1] && !map[x+1][y+1])
                        return 1;
                    else   
                        return 0;

                    break;
                case 'D': 
                    if(!map[x+2][y])
                        return 1;
                    else   
                        return 0;
                    break;
                case 'L': 
                    if(!map[x][y-1] && !map[x+1][y-1])
                        return 1;
                    else   
                        return 0;
                    break;
            }
            break;
        case Z:
        case P:
        case S:
        case H:
            switch(dir)
            {
                case 'U': 
                    if(!map[x-1][y])
                        return 1;
                    else   
                        return 0;
                    break;
                case 'R': 
                    if(!map[x][y+1])
                        return 1;
                    else   
                        return 0;
                    break;
                case 'D': 
                    if(!map[x+1][y])
                        return 1;
                    else   
                        return 0;
                    break;
                case 'L': 
                    if(!map[x][y-1])
                        return 1;
                    else   
                        return 0;
                    break;
            }
            break;
    }
    return 0;
}
//Check map whether it's completed
bool check_complete()
{
    if(map[3][1]==TT && map[3][2]==TT && map[4][1]==TT && map[4][2]==TT)
    {
        printf("Success!!!!!!!!!");
        return 1;
    }
    return 0;
}
