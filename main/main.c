#include <stdio.h>

#include "screen/screen.h"
#include "board/board.h"
#include "object/object.h"

int main()
{
        struct object_st *p_obj;
        struct board_st *p_board;

        get_board(&p_board);
        get_object(&p_obj);

	board_init(p_board, 30, 30);
      	screen_process(p_board, p_obj);
	return 0;
}
