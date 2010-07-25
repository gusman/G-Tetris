#ifndef __OBJECT_H__
#define __OBJECT_H__

#define DEGREE_0	0
#define DEGREE_90	1
#define DEGREE_180	2
#define DEGREE_270	3

#define OBJECT_T	0

#define RIGHT_COLLISION         3
#define LEFT_COLLISION          2
#define TOP_COLLISION           1
#define BOTTOM_COLLISION        0

struct object_st {
	unsigned int type;
	unsigned int rotation;
	unsigned int width;
	unsigned int height;
	int pos_x;
        int pos_y;
	unsigned int *p_plot;
        void (*pf_genplot)      (struct object_st* p_obj);
};
#define OBJECT_SETX(p_obj, x)           (p_obj)->pos_x = (x)
#define OBJECT_SETY(p_obj, y)           (p_obj)->pos_y = (y)
#define OBJECT_ROTATE(p_obj, rot)       (p_obj)->rotation = (rot)

#define OBJECT_GETX(p_obj, x)           (p_obj)->pos_x
#define OBJECT_GETY(p_obj, y)           (p_obj)->pos_y


void get_object(struct object_st** p_obj);
void object_init(struct object_st* p_obj, unsigned int obj_type, unsigned int rot);

#endif /*__OBJECT_H__*/
