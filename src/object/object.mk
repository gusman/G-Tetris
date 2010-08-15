local_dir = object
local_src = $(local_dir)/object.c $(local_dir)/object_t.c
local_obj = $(subst .c,.o,$(local_src))

sources += $(local_src)
objects += $(local_obj)
