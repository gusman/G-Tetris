#ifndef __OBJECT_T_H__
#define __OBJECT_T_H__

#include "object.h"

#define TROT_0 { \
	{ 1, 1, 1, },\
	{ 0, 1, 0, } \
}	
			
#define	TROT_90 {\
	{ 1, 0 },\
	{ 1, 1 },\
	{ 1, 0 },\
}

#define TROT_180 {\
        { 0, 1, 0, },\
	{ 1, 1, 1  } \
}

#define TROT_270 {\
	{ 0, 1 },\
	{ 1, 1 },\
	{ 0, 1 } \
}

void tobj_init(struct object_st *p_obj, unsigned int rot);
#endif /*__OBJECT_T_H__*/
