#ifndef __OBJECT_L_H__
#define __OBJECT_L_H__

#include "object.h"

#define LROT_0 { \
        { 0, 0, 1, },\
	{ 1, 1, 1  } \
}	
			
#define	LROT_90 {\
	{ 1, 0 },\
	{ 1, 0 },\
	{ 1, 1 },\
}

#define LROT_180 {\
        { 1, 1, 1, },\
        { 1, 0, 0, } \
}

#define LROT_270 {\
	{ 1, 1 },\
	{ 0, 1 },\
	{ 0, 1 } \
}

void Lobj_init(struct object_st *p_obj, unsigned int rot);
#endif /*__OBJECT_L_H__*/
