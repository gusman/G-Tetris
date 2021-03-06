#include <time.h>

#include <curses.h>

#include "board/board.h"
#include "screen/screen.h"
#include "object/object.h"

#define CLRPAIR_DEFAULT         1
#define CLRPAIR_BLOCK_T         2

#define DELAY_VAL               100

#define LOG(y, x, arg...)  \
        mvwprintw(p_wininfo, y, x, ##arg); \
        wrefresh(p_wininfo); 

WINDOW *p_winboard;
WINDOW *p_wininfo;
WINDOW *p_mirror;

void sleep(unsigned int mseconds)
{
        clock_t goal = mseconds + clock();
        while (goal > clock());
}

void screen_drawobject(WINDOW *p_window, struct object_st* p_obj, unsigned int mode)
{
        int i, j;
        int abs_x, abs_y;
        int obj_idx;

        p_obj->pf_genplot(p_obj);

        for (i = 0; i < p_obj->height; i++) {
                for (j = 0; j < p_obj->width; j++) {
                        abs_x = p_obj->pos_x + j;
                        abs_y = p_obj->pos_y + i;
                        obj_idx = (i * p_obj->width) + j;

                        wmove(p_window, abs_y, abs_x);
                        if (DRAW_FILL == mode) {
                                if (p_obj->p_plot[obj_idx] == 1) {
                                        wattron(p_window, COLOR_PAIR(CLRPAIR_BLOCK_T));
                                        wprintw(p_window, " ");
                                        wattroff(p_window, COLOR_PAIR(CLRPAIR_BLOCK_T));
                                }
                        }
                        else 
                                wprintw(p_window, " ");
                        
                        wrefresh(p_window);
                }
        }
}

void screen_drawbottom(WINDOW *p_window, struct board_st* p_board)
{
        int i, j;
        int idx;


        for (i = 0; i < p_board->height; i++) {
                for (j = 0; j < p_board->width; j++) {
                        idx = (i * p_board->width) + j;

                        wmove(p_window, i, j);
                        if (1 == p_board->p_plot[idx]) {
                               wattron(p_window, COLOR_PAIR(CLRPAIR_BLOCK_T));
                               wprintw(p_window, "1");
                               wattroff(p_window, COLOR_PAIR(CLRPAIR_BLOCK_T));
                        } else
                                wprintw(p_window, "0");
                        wrefresh(p_window);
                }
        }
}

void screen_infodraw(WINDOW *p_window, struct board_st* p_board, struct object_st* p_obj)
{
        int x;
        int y;

        x = 1;
        y = 1;

        mvwprintw(p_window, y++, x, "Board  W: %3d", p_board->width);
        mvwprintw(p_window, y++, x, "Board  H: %3d", p_board->height);
        mvwprintw(p_window, y++, x, "Obj    W: %3d", p_obj->width);
        mvwprintw(p_window, y++, x, "Obj    H: %3d", p_obj->height);     
        mvwprintw(p_window, y++, x, "Obj    X: %3d", p_obj->pos_x);
        mvwprintw(p_window, y++, x, "Obj    Y: %3d", p_obj->pos_y);
        mvwprintw(p_window, y++, x, "Obj  Y+H: %3d", p_obj->pos_y + p_obj->height);
        wrefresh(p_window);
}

void create_colorpair()
{
        init_pair(CLRPAIR_DEFAULT, COLOR_BLACK, COLOR_WHITE);
        init_pair(CLRPAIR_BLOCK_T, COLOR_WHITE, COLOR_BLUE);
}

void init_screen(void)
{
        initscr();
        start_color();
        create_colorpair();
        cbreak();
        noecho();
        refresh();
}

void create_winboard(WINDOW **p_win, struct board_st* p_board)
{
        *p_win = newwin(p_board->height, p_board->width, 0, 0);
        nodelay(*p_win, TRUE);
        keypad(*p_win, TRUE);
        wbkgd(*p_win, COLOR_PAIR(CLRPAIR_DEFAULT));
        wrefresh(*p_win);
}

void create_mirror(WINDOW **p_win, struct board_st* p_board)
{
        *p_win = newwin(p_board->height, p_board->width, 0, 70);
        nodelay(*p_win, TRUE);
        keypad(*p_win, TRUE);
        wbkgd(*p_win, COLOR_PAIR(CLRPAIR_DEFAULT));
        wrefresh(*p_win);

}

void create_wininfo(WINDOW **p_win, struct board_st* p_board)
{
        *p_win = newwin(30, 35, 0, p_board->width + 2);
        box(*p_win, 0, 0);
        wbkgd(*p_win, COLOR_PAIR(CLRPAIR_DEFAULT));
        wrefresh(*p_win);
}

void screen_keyhandler(int key, struct board_st* p_board, struct object_st* p_obj)
{ 
        switch(key) {
                case KEY_UP:
                        LOG( 9, 1, "Key: KEY_UP   ");
                        napms(DELAY_VAL);
                        screen_drawobject(p_winboard, p_obj, DRAW_CLEAR);
                        p_obj->rotation = (p_obj->rotation + 1) % 4;
                        if ( (board_collisiondetect(LEFT_COLLISION, p_board, p_obj)) 
                                || (board_collisiondetect(LEFT_COLLISION, p_board, p_obj))
                                || (board_collisiondetect(LEFT_COLLISION, p_board, p_obj))
                                || (board_collisiondetect(LEFT_COLLISION, p_board, p_obj)) ) 
                                p_obj->rotation = (p_obj->rotation - 1) % 4;
                        screen_drawobject(p_winboard, p_obj, DRAW_FILL);
                        break;

                case KEY_DOWN:
                        LOG( 9, 1, "Key: KEY_DOWN ");
                        napms(DELAY_VAL);
                        screen_drawobject(p_winboard, p_obj, DRAW_CLEAR);
                        p_obj->rotation = (p_obj->rotation - 1) % 4;
                        break;

                case KEY_LEFT:
                        LOG( 9, 1, "Key: KEY_LEFT ");
                        if (!board_collisiondetect(LEFT_COLLISION, p_board, p_obj)) {
                                LOG(10, 1, "<<< LEFT COLL >>>"); 
                                napms(DELAY_VAL);
                                screen_drawobject(p_winboard, p_obj, DRAW_CLEAR);
                                p_obj->pos_x--;
                                screen_drawobject(p_winboard, p_obj, DRAW_FILL);
                        }
                        break;

                case KEY_RIGHT:
                        LOG( 9, 1, "Key: KEY_RIGHT");
                        if (!board_collisiondetect(RIGHT_COLLISION, p_board, p_obj)) {
                                LOG(10, 1, "<<< RGHT COLL >>>");
                                napms(DELAY_VAL);
                                screen_drawobject(p_winboard, p_obj, DRAW_CLEAR);
                                p_obj->pos_x++;
                                screen_drawobject(p_winboard, p_obj, DRAW_FILL);
                        } 
                        break;
        }
}


void screen_process(struct board_st* p_board, struct object_st* p_obj)
{
        /* Init screen */
        init_screen();
        create_winboard(&p_winboard, p_board);
        create_wininfo(&p_wininfo, p_board); 
        create_mirror(&p_mirror, p_board);

        /* Init and create object */
        object_init(p_obj, OBJECT_Z, DEGREE_0);

        p_obj->pos_y = 0;
        p_obj->pos_x = 31;
        while(1) {
                int ch;

                if (0 == p_obj->pos_y) {
                        if ((p_obj->pos_x + 1)>= 30) 
                                p_obj->pos_x = 0;
                        else
                                p_obj->pos_x += 1;

                        p_obj->rotation = 0;
                }

                screen_drawobject(p_winboard, p_obj, DRAW_FILL);
                screen_infodraw(p_wininfo, p_board, p_obj);
                
                ch = wgetch(p_winboard);
                if ('Q' == ch || 'q' == ch)
                        break;

                screen_keyhandler(ch, p_board, p_obj);

                if (board_collisiondetect(TOP_COLLISION, p_board, p_obj)) {
                        LOG(10, 1, "<<< GAME OVER >>>");
                        break;
                } else if (board_collisiondetect(BOTTOM_COLLISION, p_board, p_obj)) {
                        board_plotobject(p_board, p_obj);
                        board_checkscore(p_board, p_obj);
                        screen_drawbottom(p_winboard, p_board);
                        screen_drawbottom(p_mirror, p_board);
                        LOG(11, 1, "TOP_ROW : %d\n", p_board->top_row);
                        p_obj->pos_y = 0;
                } else {
                        napms(DELAY_VAL);
                        screen_drawobject(p_winboard, p_obj, DRAW_CLEAR);
                        p_obj->pos_y++;
                }

        }      
        endwin();
}
