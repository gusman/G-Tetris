#ifndef __OBJECT_J_H__
#define __OBJECT_J_H__

#include "object.h"

#define JROT_0 { \
        { 1, 0, 0, },\
	{ 1, 1, 1  } \
}	
			
#define	JROT_90 {\
	{ 1, 1 },\
	{ 1, 0 },\
	{ 1, 0 },\
}

#define JROT_180 {\
        { 1, 1, 1, },\
        { 0, 0, 1, } \
}

#define JROT_270 {\
	{ 0, 1 },\
	{ 0, 1 },\
	{ 1, 1 } \
}

void jobj_init(struct object_st *p_obj, unsigned int rot);
#endif /*__OBJECT_J_H__*/
