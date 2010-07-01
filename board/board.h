#ifndef __BOARD_H__
#define __BOARD_H__

#include "object\object.h"

struct board_st {
	unsigned int width;
	unsigned int height;
        unsigned int *p_plot;
};

void get_board(struct board_st** p_board);
void board_init(struct board_st* p_board, unsigned int width, unsigned int height);
void board_drawobject(struct object_st* p_obj, unsigned int mode);
void board_process(struct board_st* p_board, struct object_st* p_obj);
#endif /*__BOARD_H__*/

