local_dir = object
local_src = $(local_dir)/object.c \
	    $(local_dir)/object_t.c \
	    $(local_dir)/object_i.c \
	    $(local_dir)/object_o.c \
	    $(local_dir)/object_j.c \
	    $(local_dir)/object_l.c \
	    $(local_dir)/object_s.c \
	    $(local_dir)/object_z.c \

local_obj = $(subst .c,.o,$(local_src))

sources += $(local_src)
objects += $(local_obj)
