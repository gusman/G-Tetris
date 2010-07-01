#include <windows.h>
#include <time.h>

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
 
void sleep(unsigned int mseconds)
{
        clock_t goal = mseconds + clock();
        while (goal > clock());
}

