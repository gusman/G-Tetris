#include <time.h>

#include <curses.h>

#include "board/board.h"
#include "screen/screen.h"
#include "object/object.h"

void sleep(unsigned int mseconds)
{
        clock_t goal = mseconds + clock();
        while (goal > clock());
}

#if 0 /*It seems we don't need this anymore */
static void screen_drawborder(struct board_st* p_board)
{
	int i;
	int j;


	for (i = 0; i < p_board->width; i++) {
		printw("%c", 219);
                p_board->p_plot[i] = BORDER_VAL;
	}

	for(j = 1; j < p_board->height; j++) {
		printw("%c", 219);
                p_board->p_plot[(i - 1) + (j * p_board->width)] = BORDER_VAL;

		printw("%c", 219);
                p_board->p_plot[(j * p_board->width)] = BORDER_VAL;
	}
	
	for (i = 1; i < p_board->width; i++) {
		printw("%c", 219);
                p_board->p_plot[i + ((j - 1) * p_board->width)] = BORDER_VAL;
	}
}
#endif 
void screen_drawobject(struct object_st* p_obj, unsigned int mode)
{
        int i;
        int cur_x, cur_y;
        unsigned int line;

        p_obj->pf_genplot(p_obj);

        line = (p_obj->pos_y == 0) ? 0 : (p_obj->pos_y - 1);
        for (i = 0; i < (p_obj->width * p_obj->height); i++) {
                if (0 == (i % p_obj->width)) 
                        line++;

                cur_x = (i % p_obj->width) + p_obj->pos_x;
                cur_y = line;
                move(cur_y, cur_x);

                if (DRAW_FILL == mode) {
                        if (p_obj->p_plot[i] == 1) {
                                printw("%c", 219);
                        }
                }
                else {
                        printw("%c", 32);
                }
                refresh();
        }
}

void screen_drawplot(struct board_st* p_board)
{
        int i, j;
	for (i = 0; i < p_board->height; i++) {
                /* gotoyx(2, i + 34); */
                for (j = 0; j < p_board->width; j++) {
                        printw("%2d", p_board->p_plot[(i * p_board->width) + j]);
                
                }
	}

        for (i = 0; i < p_board->height; i++) {
              /*  gotoyx(0, i + 34); printw("%2d", i); */
        } 

        /* gotoyx(2, i + 34); */
        for (j = 0; j < p_board->width; j++) {
                printw("%2d", j);
        }
}


void screen_process(struct board_st* p_board, struct object_st* p_obj)
{
        unsigned int pos_x;
        unsigned int pos_y;


        object_init(p_obj, OBJECT_T, DEGREE_0);

        initscr();
        noecho();

        pos_x = p_board->width / 2;
        pos_y = 0;

        while(1) {


                p_obj->pos_x = pos_x;
                p_obj->pos_y = pos_y;
                p_obj->rotation = DEGREE_270;

                /*
                gotoyx(45,0); printw("w: %4d", p_obj->width);
                gotoyx(45,1); printw("h: %4d", p_obj->height);
                gotoyx(45,2); printw("x: %4d", p_obj->pos_x);
                gotoyx(45,3); printw("y: %4d", p_obj->pos_y);
                */
                screen_drawobject(p_obj, DRAW_FILL);
                //getch();
                sleep(25);
/*
                if (board_collisiondetect(BOTTOM_COLLISION, p_board, p_obj)) {
                        board_plotobject(p_board, p_obj);
                        screen_drawplot(p_board);
                        pos_y = 0;
                        continue;
                }

                screen_drawobject(p_obj, DRAW_CLEAR);
                */
                pos_y++;
                if (20 < pos_y) pos_y = 0;
        }      
        endwin();
}
