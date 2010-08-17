#include <stdio.h>

#include "object.h"
#include "object_t.h"
#include "object_i.h"
#include "object_o.h"
#include "object_j.h"
#include "object_s.h"

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

                case OBJECT_I:
                        iobj_init(p_obj, rot);
                break;
                
                case OBJECT_O:
                        oobj_init(p_obj, rot);
                break;

                case OBJECT_J:
                        jobj_init(p_obj, rot);
                break;
                
                case OBJECT_L:
                        lobj_init(p_obj, rot);
                break;

                case OBJECT_S:
                        sobj_init(p_obj, rot);
                break;

                case OBJECT_Z:
                        zobj_init(p_obj, rot);
                break;
        }
}


