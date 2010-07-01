local_dir = main
local_src = $(local_dir)\main.c
local_obj = $(subst .c,.o,$(local_src))

sources += $(local_src)
objects += $(local_obj)
