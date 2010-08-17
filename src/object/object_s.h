#ifndef __OBJECT_S_H__
#define __OBJECT_S_H__

#include "object.h"

#define SROT_0 { \
        { 0, 1, 1, },\
	{ 1, 1, 0  } \
}	
			
#define	SROT_90 {\
	{ 1, 0 },\
	{ 1, 1 },\
	{ 0, 1 },\
}

#define SROT_180        SROT_0
#define SROT_270        SROT_90

void sobj_init(struct object_st *p_obj, unsigned int rot);
#endif /*__OBJECT_S_H__*/
