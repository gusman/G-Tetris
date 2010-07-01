#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "board.h"
#include "screen/screen.h"
#include "object/object.h"

#define OBJECT_LINE_START       1

#define DRAW_FILL               1
#define DRAW_CLEAR              0
#define BOARD_BORDER            1

#define BORDER_VAL              2
#define PLOTTED_VAL             3

static struct board_st st_board;

static void board_drawborder(struct board_st* p_board);

void get_board(struct board_st** p_board)
{
	*p_board = (struct board_st*) &st_board;
}

void board_init(struct board_st* p_board, unsigned int width, unsigned int height)
{
	p_board->width = width;
	p_board->height = height;
        p_board->p_plot = (unsigned int *) malloc(sizeof(unsigned int) * p_board->width * p_board->height);
        memset(p_board->p_plot, 0, sizeof(unsigned int) * p_board->width * p_board->height);
        board_drawborder(p_board);
}

static void board_drawborder(struct board_st* p_board)
{
	int i;
	int j;

	clrscr();

	for (i = 0; i < p_board->width; i++) {
		gotoxy(i, 0);
		printf("%c", 219);
                p_board->p_plot[i] = BORDER_VAL;
	}

	for(j = 1; j < p_board->height; j++) {
		gotoxy(i - 1, j);
		printf("%c", 219);
                p_board->p_plot[(i - 1) + (j * p_board->width)] = BORDER_VAL;

		gotoxy(0, j);
		printf("%c", 219);
                p_board->p_plot[(j * p_board->width)] = BORDER_VAL;
	}
	
	for (i = 1; i < p_board->width; i++) {
		gotoxy(i, j - 1);
		printf("%c", 219);
                p_board->p_plot[i + ((j - 1) * p_board->width)] = BORDER_VAL;
	}
}

void board_drawobject(struct object_st* p_obj, unsigned int mode)
{
        int i;
        unsigned int line;
        gotoxy(45,10); printf("obj->x: %d", p_obj->pos_x);
        gotoxy(45,11); printf("obj->y: %d", p_obj->pos_y);

        p_obj->pf_genplot(p_obj);

 
        line = (p_obj->pos_y == 0) ? 0 : (p_obj->pos_y - 1);
        for (i = 0; i < (p_obj->width * p_obj->height); i++) {
                if (0 == (i % p_obj->width)) 
                        line++;

                gotoxy((i % p_obj->width) + p_obj->pos_x, line);

                if (DRAW_FILL == mode) {
                        if (p_obj->p_plot[i] == 1) {
                                printf("%c", 219);
                        }
                }
                else {
                        printf("%c", 32);
                }

        }
}

void board_plotobject(struct board_st* p_board, struct object_st* p_obj)
{
        int i;
        unsigned int board_index;
        for (i = 0; i < (p_obj->height * p_obj->width); i++) {
                if (1 == p_obj->p_plot[i]) {
                        board_index =  ((i / p_obj->width) + p_obj->pos_y) * p_board->width;
                        board_index += (i % p_obj->width) + p_obj->pos_x;
                        p_board->p_plot[board_index] = /*p_obj->p_plot[i]*/ PLOTTED_VAL;
                }

        }

}

/* NEED SIMPLIFIED COLLISION */
int board_collisiondetect(unsigned int coll_mode, struct board_st* p_board, struct object_st* p_obj) 
{
        int row_ctr, col_ctr, board_x, board_y; 
        unsigned int board_idx, obj_idx;
        int ret_val;

        ret_val = 0;
        switch(coll_mode)
        {
                case BOTTOM_COLLISION:
                        for (row_ctr = p_obj->height - 1; row_ctr >= 0; row_ctr--) {
                                for(col_ctr = 0; col_ctr < p_obj->width; col_ctr++) {
                                       obj_idx = (row_ctr * p_obj->width) + col_ctr;

                                       if (1 == p_obj->p_plot[obj_idx]) {
                                               board_x = p_obj->pos_x + col_ctr;
                                               board_y = p_obj->pos_y + row_ctr + 1;

                                               board_idx = (board_y * p_board->width) + board_x;
                                               
                                               switch (p_board->p_plot[board_idx]) 
                                               {
                                                        case 2:
                                                        case 3:
                                                                ret_val = 1;
                                                                break;
                                               }
                                       }

                                       if (1 == ret_val) break;
                                }
                        }
                        break;

                case TOP_COLLISION:
                        break;
        }
         

        gotoxy(45, 6); printf("                     ");
        return ret_val;
}



void board_drawplot(struct board_st* p_board)
{
        int i, j;
	for (i = 0; i < p_board->height; i++) {
                gotoxy(2, i + 34);
                for (j = 0; j < p_board->width; j++) {
                        printf("%2d", p_board->p_plot[(i * p_board->width) + j]);
                
                }
	}

        for (i = 0; i < p_board->height; i++) {
                gotoxy(0, i + 34); printf("%2d", i);
        } 

        gotoxy(2, i + 34); 
        for (j = 0; j < p_board->width; j++) {
                printf("%2d", j);
        }
}

void board_process(struct board_st* p_board, struct object_st* p_obj)
{
        unsigned int pos_x;
        unsigned int pos_y;

        pos_x = p_board->width / 2;
        pos_y = 0;

        while(1) {


                p_obj->pos_x = pos_x;
                p_obj->pos_y = pos_y;
                p_obj->rotation = DEGREE_270;

                gotoxy(45,0); printf("w: %4d", p_obj->width);
                gotoxy(45,1); printf("h: %4d", p_obj->height);
                gotoxy(45,2); printf("x: %4d", p_obj->pos_x);
                gotoxy(45,3); printf("y: %4d", p_obj->pos_y);

                board_drawobject(p_obj, DRAW_FILL);
                sleep(25);

                if (board_collisiondetect(BOTTOM_COLLISION, p_board, p_obj)) {
                        board_plotobject(p_board, p_obj);
                        board_drawplot(p_board);
                        pos_y = 0;
                        continue;
                }

                board_drawobject(p_obj, DRAW_CLEAR);

                pos_y++;
        }      
}
