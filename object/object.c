#include <stdio.h>

#include "object.h"
#include "object_t.h"

static struct object_st st_obj;

void get_object(struct object_st** p_obj)
{
        *p_obj = (struct object_st*) &st_obj;
}

void object_init(struct object_st* p_obj, unsigned int obj_type, unsigned int rot)
{
	switch(obj_type)
	{
		case OBJECT_T:
			tobj_init(p_obj, rot);
		break;
	}
}


