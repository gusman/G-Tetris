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

	board_init(p_board, 25, 25);
	object_init(p_obj, OBJECT_T, DEGREE_90);

        board_process(p_board, p_obj);
      	
        gotoxy(0,45);        
	return 0;
}
