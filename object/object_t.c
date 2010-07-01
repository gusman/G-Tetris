#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "object/object.h"
#include "object/object_t.h"

#define TOBJ_W	3
#define TOBJ_H	2

void tobj_genplot0(struct object_st *p_obj);
void tobj_genplot90(struct object_st *p_obj);
void tobj_genplot180(struct object_st *p_obj);
void tobj_genplot270(struct object_st *p_obj);
void tobj_genplot(struct object_st *p_obj);

void tobj_init(struct object_st *p_obj, unsigned int rot)
{
	p_obj->type = OBJECT_T;
	p_obj->rotation = rot;
	p_obj->pos_x = 0;
        p_obj->pos_y = 0;
	p_obj->width = TOBJ_W;
	p_obj->height = TOBJ_H;

        OBJECT_SETX(p_obj, 0);
        OBJECT_SETY(p_obj, 0);
        OBJECT_ROTATE(p_obj, DEGREE_90);

        free(p_obj->p_plot);
	p_obj->p_plot = (unsigned int *) malloc(sizeof(unsigned int) * (TOBJ_W * TOBJ_H));
        p_obj->pf_genplot = tobj_genplot;
}

void tobj_genplot(struct object_st *p_obj)
{
        switch(p_obj->rotation)
        {
                case DEGREE_0:
                        tobj_genplot0(p_obj);
                        break;

                case DEGREE_90:
                        tobj_genplot90(p_obj);
                        break;

                case DEGREE_180:
                        tobj_genplot180(p_obj);
                        break;

                case DEGREE_270:
                        tobj_genplot270(p_obj);
                        break;
        }
}

int tobj_detectcollision(struct object_st *p_obj, unsigned int coll)
{
        switch(coll)
        {
                case TOP_COLLISION:

                        break;

                case BOTTOM_COLLISION:

                        break;

        }
}

void tobj_genplot0(struct object_st *p_obj)
{
	unsigned int arr_tobj[TOBJ_H][TOBJ_W] = TROT_0;

        p_obj->width = TOBJ_W;
        p_obj->height = TOBJ_H;
        memcpy(p_obj->p_plot, arr_tobj, sizeof(int) * TOBJ_W * TOBJ_H);
}	

void tobj_genplot90(struct object_st *p_obj)
{
	unsigned int arr_tobj[TOBJ_W][TOBJ_H] = TROT_90;

        p_obj->width = TOBJ_H;
        p_obj->height = TOBJ_W;
        memcpy(p_obj->p_plot, arr_tobj, sizeof(int) * TOBJ_W * TOBJ_H);
}

void tobj_genplot180(struct object_st *p_obj)
{
	unsigned int arr_tobj[TOBJ_H][TOBJ_W] = TROT_180;

        p_obj->width = TOBJ_W;
        p_obj->height = TOBJ_H;
        memcpy(p_obj->p_plot, arr_tobj, sizeof(int) * TOBJ_W * TOBJ_H);
}

void tobj_genplot270(struct object_st *p_obj)
{
	unsigned int arr_tobj[TOBJ_W][TOBJ_H] = TROT_270;

        p_obj->width = TOBJ_H;
        p_obj->height = TOBJ_W;
        memcpy(p_obj->p_plot, arr_tobj, sizeof(int) * TOBJ_W * TOBJ_H);
}
