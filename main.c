/*
main.c:
    This is the main program for running chinese puzzle!
*/
#include <stdio.h>
#include "map.h"
int main()
{
    init();
    status();
    char s[20];
    while(!check_complete())
    {
        printf("Input Your Move :(FU,FR,FD,FL,SU,SR,SD,SL)\n");
        scanf("%s",s);
        move(s);
        status();
    }
	return 0;
}
