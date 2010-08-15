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
        p_board->top_row = p_board->height - 1;
        p_board->score = 0;
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
        
        /* Update boar top filled row */
        if (p_obj->pos_y < p_board->top_row)
                p_board->top_row = p_obj->pos_y;

}

/* NEED SIMPLIFIED COLLISION */
int board_collisiondetect(unsigned int coll_mode, struct board_st* p_board, struct object_st* p_obj) 
{
        int i, j;
        int obj_idx;
        int abs_x, abs_y, abs_idx; 

        switch(coll_mode)
        {
                case BOTTOM_COLLISION:
                {
                        /* Check window border */
                        if ((p_obj->pos_y + p_obj->height) >= (p_board->height)) {
                                return 1;
                        }
                
                        /* Check plotted collision */
                        /* Detection starts from left to right in last row */
                        for (i = p_obj->height - 1; i >= 0 ; i--) {
                                for (j = 0; j < p_obj->width; j++) {
                                        obj_idx =  (i * p_obj->width) + j;  

                                        if (PLOTTED_VAL == p_obj->p_plot[obj_idx]) {
                                                abs_x = p_obj->pos_x + j;
                                                abs_y = p_obj->pos_y + i;   
                                                
                                                abs_idx = ((abs_y + 1) * p_board->width) + abs_x;
                                                if (PLOTTED_VAL == p_board->p_plot[abs_idx])
                                                        return 1;
                                        }
                                }
                        }
                }
                break;

                case TOP_COLLISION:
                {
                        if (board_collisiondetect(BOTTOM_COLLISION, p_board, p_obj)) {
                                /* Check window border */
                                if (0 == p_obj->pos_y)
                                        return 1;
                        }

                        return 0;
                }
                break;

                case LEFT_COLLISION:
                {
                        if (0 >= p_obj->pos_x)
                                return 1;

                        for (j = 0; j < p_obj->width; j++) {
                                for (i = 0; i < p_obj->height; i++) {
                                        obj_idx =  (i * p_obj->width) + j;

                                        if (PLOTTED_VAL == p_obj->p_plot[obj_idx]) {
                                                abs_x = p_obj->pos_x + j;
                                                abs_y = p_obj->pos_y + i;

                                                abs_idx = ((abs_y) * p_board->width) + (abs_x - 1);
                                                if (PLOTTED_VAL == p_board->p_plot[abs_idx])
                                                        return 1;
                                        }
                                }
                        }
                        return 0;
                }
                break;

                case RIGHT_COLLISION:
                {
                        if (p_board->width <= (p_obj->pos_x + p_obj->width))
                                return 1;

                        for (j = p_obj->width - 1; j >= 0; j--) {
                                for (i = 0; i < p_obj->height; i++) {
                                        obj_idx =  (i * p_obj->width) + j;

                                        if (PLOTTED_VAL == p_obj->p_plot[obj_idx]) {
                                                abs_x = p_obj->pos_x + j;
                                                abs_y = p_obj->pos_y + i;

                                                abs_idx = ((abs_y) * p_board->width) + (abs_x + 1);
                                                if (PLOTTED_VAL == p_board->p_plot[abs_idx])
                                                        return 1;
                                        }
                                }
                        }

                        return 0;
                };
        }
         
        return 0;
}


#include <curses.h>
extern WINDOW *p_wininfo;
#undef LOG(y, x, arg..)
#define LOG(y, x, arg...)  \
        mvwprintw(p_wininfo, y, x, ##arg); \
        wrefresh(p_wininfo); 

void board_shiftdown(struct board_st* p_board, unsigned int shift_val)
{
        int max_y;
        int min_y;

        max_y = p_board->height - 1;
        min_y = max_y - shift_val;
        for (; max_y >= min_y - 1; max_y--){
                int i;
                int source_idx;
                int target_idx;
                
                for (i = 0; i < p_board->width; i++) {
                        source_idx = ((max_y - 1) * p_board->width) + i;
                        target_idx = (max_y * p_board->width) + i;

                        p_board->p_plot[target_idx] = p_board->p_plot[source_idx];
                }
        }

}

int board_scanrow(struct board_st* p_board, unsigned int row_idx)
{
        int i;
        int abs_idx;
        
        for (i = 0; i < p_board->width; i++) {
                abs_idx = (row_idx * p_board->width) + i;
                if (UNPLOTTED_VAL == p_board->p_plot[abs_idx])
                                return 0;

                LOG(14, i+1, " %d", i);
        }

        return 1;
}

int board_checkscore(struct board_st* p_board, struct object_st* p_obj)
{
        int i, shift_val;
        int y;

        if (board_scanrow(p_board, p_board->height-1))
                board_shiftdown(p_board, 1);
        /*
        y = p_board->height - 1;
        while(1) {

                shift_val = 0;
                while (board_scanrow(p_board, y)) {
                        y--;
                        shift_val++;
                        p_board->score++;

                        LOG(13, 1, "shift-val: %d", shift_val);

                        if (y < p_board->top_row);
                                break;
                }

                LOG(12,1, "shift val: %d", shift_val);

                if (shift_val != 0) board_shiftdown(p_board, 1);

                p_board->top_row -= shift_val;
                y += shift_val - 1;

                if (y < p_board->top_row)
                        break;
        }
*/
        return p_board->score;
}
