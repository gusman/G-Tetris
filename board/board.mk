local_dir = board
local_src = $(local_dir)\board.c
local_obj = $(subst .c,.o,$(local_src))

sources += $(local_src)
objects += $(local_obj)
