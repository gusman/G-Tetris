#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "board.h"
#include "screen/screen.h"
#include "object/object.h"


static struct board_st st_board;

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
         
        return ret_val;
}
