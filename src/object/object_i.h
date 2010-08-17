#ifndef __OBJECT_I_H__
#define __OBJECT_I_H__

#include "object.h"

#define	IROT_0 {\
	{ 1, 1, 1, 1 },\
}

#define IROT_90 {\
	{ 1 }, \
	{ 1 }, \
	{ 1 }, \
        { 1 }, \
}
			

#define IROT_180        IROT_0
#define IROT_270        IROT_90

void iobj_init(struct object_st *p_obj, unsigned int rot);
#endif /*__OBJECT_I_H__*/
