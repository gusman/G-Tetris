#ifndef __OBJECT_T_H__
#define __OBJECT_T_H__

#include "object.h"

#define T_WIDTH		3	
#define T_HEIGHT	3

#define TROT_0 { \
	{ 0, 1, 0, },\
	{ 1, 1, 1  } \
}	
			
#define	TROT_90 {\
	{ 1, 0 },\
	{ 1, 1 },\
	{ 1, 0 },\
}

#define TROT_180 {\
	{ 1, 1, 1, },\
	{ 0, 1, 0, } \
}

#define TROT_270 {\
	{ 0, 1 },\
	{ 1, 1 },\
	{ 0, 1 } \
}

void tobj_init(struct object_st *p_obj, unsigned int rot);
#endif /*__OBJECT_T_H__*/
