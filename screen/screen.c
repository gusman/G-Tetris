#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#ifndef D_LINUX
#include <windows.h>
#endif /*D_LINUX*/

#ifdef D_LINUX
void clrscr(void) {
int i;
 
for (i = 0; i < 100; i++)
        putchar('\n');
}
 
void gotoxy(int x, int y) {
        char essq[100]; /* String variable to hold the escape sequence */
        char xstr[100]; /* Strings to hold the x and y coordinates */
        char ystr[100]; /* Escape sequences must be built with characters */
         
        /*
        ** Convert the screen coordinates to strings
        */
        sprintf(xstr, "%d", x);
        sprintf(ystr, "%d", y);
         
        /*
        ** Build the escape sequence (vertical move)
        */
        essq[0] = '\0';
        strcat(essq, "\033[");
        strcat(essq, ystr);
         
        /*
        ** Described in man terminfo as vpa=\E[%p1%dd
        ** Vertical position absolute
        */
        strcat(essq, "d");
         
        /*
        ** Horizontal move
        ** Horizontal position absolute
        */
        strcat(essq, "\033[");
        strcat(essq, xstr);
        /* Described in man terminfo as hpa=\E[%p1%dG */
        strcat(essq, "G");
         
        /*
        ** Execute the escape sequence
        ** This will move the cursor to x, y
        */
        printf("%s", essq);
}
#else /* D_LINUX */
void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void clrscr(void)
{
	system("cls");
}
#endif /* D_LINUX */


void sleep(unsigned int mseconds)
{
        clock_t goal = mseconds + clock();
        while (goal > clock());
}

