#ifndef __BOARD_H__
#define __BOARD_H__

#include "object/object.h"


#define DRAW_FILL               1
#define DRAW_CLEAR              0
#define BOARD_BORDER            1

#define PLOTTED_VAL             1
#define UNPLOTTED_VAL           0


struct board_st {
	unsigned int width;
	unsigned int height;
        unsigned int *p_plot;
};


void get_board(struct board_st** p_board);
void board_init(struct board_st* p_board, unsigned int width, unsigned int height);
void board_plotobject(struct board_st* p_board, struct object_st* p_obj);
int board_collisiondetect(unsigned int coll_mode, struct board_st* p_board, struct object_st* p_obj); 
#endif /*__BOARD_H__*/

