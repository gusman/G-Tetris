local_dir = screen
local_src = $(local_dir)/screen.c
local_obj = $(subst .c,.o,$(local_src))

sources += $(local_src)
objects += $(local_obj)
