#ifndef __OBJECT_Z_H__
#define __OBJECT_Z_H__

#include "object.h"

#define ZROT_0 { \
        { 1, 1, 0, },\
	{ 0, 1, 1  } \
}	
			
#define	ZROT_90 {\
	{ 0, 1 },\
	{ 1, 1 },\
	{ 1, 0 },\
}

#define ZROT_180        ZROT_0
#define ZROT_270        ZROT_90

void zobj_init(struct object_st *p_obj, unsigned int rot);
#endif /*__OBJECT_Z_H__*/
