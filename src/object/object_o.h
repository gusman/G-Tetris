#ifndef __OBJECT_O_H__
#define __OBJECT_O_H__

#include "object.h"

#define	OROT_0 {\
	{ 1, 1 },\
	{ 1, 1 },\
}

#define OROT_90         OROT_0
#define OROT_180        OROT_0
#define OROT_270        OROT_0

void oobj_init(struct object_st *p_obj, unsigned int rot);
#endif /*__OBJECT_T_H__*/
