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
void screen_drawobject(WINDOW *p_window, struct object_st* p_obj, unsigned int mode)
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
                wmove(p_window, cur_y, cur_x);

                if (DRAW_FILL == mode) {
                        if (p_obj->p_plot[i] == 1) {
                                wattron(p_window, COLOR_PAIR(1));
                                wprintw(p_window, " ");
                                wattroff(p_window, COLOR_PAIR(1));
                        }
                }
                else {
                        wprintw(p_window, " ");
                }
                wrefresh(p_window);
        }

}

void screen_drawplot(WINDOW *p_window, struct board_st* p_board)
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

void screen_info(WINDOW *p_window, struct board_st* p_board, struct object_st* p_obj)
{
        int x;
        int y;

        x = 1;
        y = 1;

        mvwprintw(p_window, y++, x, "Board W: %3d", p_board->width);
        mvwprintw(p_window, y++, x, "Board H: %3d", p_board->height);
        mvwprintw(p_window, y++, x, "Obj   X: %3d", p_obj->pos_x);
        mvwprintw(p_window, y++, x, "Obj   Y: %3d", p_obj->pos_y);
        wrefresh(p_window);
}

#define LOG(y, x, s)  \
        mvwprintw(p_wininfo, y, x, s); \
        wrefresh(p_wininfo); 


void screen_process(struct board_st* p_board, struct object_st* p_obj)
{
        WINDOW *p_winboard;
        WINDOW *p_wininfo;

        int pos_x;
        int pos_y;

        /* Init and create object */
        object_init(p_obj, OBJECT_T, DEGREE_0);
        pos_x = p_board->width / 2;
        pos_y = 0;

                /* Init screen */
        initscr();
        cbreak();
        noecho();
        refresh();

        /* Create Board Window */
        p_winboard = newwin(p_board->height, p_board->width, 0, 0);
        nodelay(p_winboard, TRUE);
        keypad(p_winboard, TRUE);
        box(p_winboard, 0, 0);
        wrefresh(p_winboard);

        /* Create Board Info */
        p_wininfo = newwin(p_board->height >> 1, 35, 0, p_board->width + 2);
        box(p_wininfo, 0, 0);
        wrefresh(p_wininfo);

        /* Color */
        start_color();
        init_pair(1, COLOR_WHITE, COLOR_BLACK);
        init_pair(2, COLOR_BLACK, COLOR_WHITE);

        wbkgd(p_winboard, COLOR_PAIR(2));
        wbkgd(p_wininfo, COLOR_PAIR(2));
 
        while(1) {
                int ch;

                if (0 == pos_y)
                        p_obj->pos_x = pos_x;

                p_obj->pos_y = pos_y;

                screen_drawobject(p_winboard, p_obj, DRAW_FILL);
                screen_info(p_wininfo, p_board, p_obj);

                ch = wgetch(p_winboard);
                if ('Q' == ch || 'q' == ch)
                        break;

                napms(250);
                screen_drawobject(p_winboard, p_obj, DRAW_CLEAR);
                switch(ch) {
                        case KEY_UP:
                                LOG( 7, 1, "Key: KEY_UP   ");
                                p_obj->rotation = (p_obj->rotation + 1) % 4;
                                break;

                        case KEY_DOWN:
                                LOG( 7, 1, "Key: KEY_DOWN ");
                                p_obj->rotation = (p_obj->rotation - 1) % 4;
                                break;

                        case KEY_LEFT:
                                LOG( 7, 1, "Key: KEY_LEFT ");
                                p_obj->pos_x = ((p_obj->pos_x - 1) > 0) ? p_obj->pos_x - 1 : 0;
                                break;

                        case KEY_RIGHT:
                                LOG( 7, 1, "Key: KEY_RIGHT");
                                p_obj->pos_x = ((p_obj->pos_x + 1) < p_board->width) ? p_obj->pos_x + 1 : p_board->width;
                                break;
                }

               
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
                if ((p_board->height - 4) < pos_y) pos_y = 0;
        }      
        endwin();
}
