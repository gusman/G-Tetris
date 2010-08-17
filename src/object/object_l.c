#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "object/object.h"
#include "object/object_l.h"

#define LOBJ_W	3
#define LOBJ_H	2

void lobj_genplot0(struct object_st *p_obj);
void lobj_genplot90(struct object_st *p_obj);
void lobj_genplot180(struct object_st *p_obj);
void lobj_genplot270(struct object_st *p_obj);
void lobj_genplot(struct object_st *p_obj);

void lobj_init(struct object_st *p_obj, unsigned int rot)
{
	p_obj->type = OBJECT_L;
	p_obj->rotation = rot;
	p_obj->pos_x = 0;
        p_obj->pos_y = 0;
	p_obj->width = LOBJ_W;
	p_obj->height = LOBJ_H;

        OBJECT_SETX(p_obj, 0);
        OBJECT_SETY(p_obj, 0);
        OBJECT_ROTATE(p_obj, DEGREE_90);

        free(p_obj->p_plot);
	p_obj->p_plot = (unsigned int *) malloc(sizeof(unsigned int) * (LOBJ_W * LOBJ_H));
        p_obj->pf_genplot = lobj_genplot;
}

void lobj_genplot(struct object_st *p_obj)
{
        switch(p_obj->rotation)
        {
                case DEGREE_0:
                        lobj_genplot0(p_obj);
                        break;

                case DEGREE_90:
                        lobj_genplot90(p_obj);
                        break;

                case DEGREE_180:
                        lobj_genplot180(p_obj);
                        break;

                case DEGREE_270:
                        lobj_genplot270(p_obj);
                        break;
        }
}


void lobj_genplot0(struct object_st *p_obj)
{
	unsigned int arr_lobj[LOBJ_H][LOBJ_W] = LROT_0;

        p_obj->width = LOBJ_W;
        p_obj->height = LOBJ_H;
        memcpy(p_obj->p_plot, arr_lobj, sizeof(int) * LOBJ_W * LOBJ_H);
}	

void lobj_genplot90(struct object_st *p_obj)
{
	unsigned int arr_lobj[LOBJ_W][LOBJ_H] = LROT_90;

        p_obj->width = LOBJ_H;
        p_obj->height = LOBJ_W;
        memcpy(p_obj->p_plot, arr_lobj, sizeof(int) * LOBJ_W * LOBJ_H);
}

void lobj_genplot180(struct object_st *p_obj)
{
	unsigned int arr_lobj[LOBJ_H][LOBJ_W] = LROT_180;

        p_obj->width = LOBJ_W;
        p_obj->height = LOBJ_H;
        memcpy(p_obj->p_plot, arr_lobj, sizeof(int) * LOBJ_W * LOBJ_H);
}

void lobj_genplot270(struct object_st *p_obj)
{
	unsigned int arr_lobj[LOBJ_W][LOBJ_H] = LROT_270;

        p_obj->width = LOBJ_H;
        p_obj->height = LOBJ_W;
        memcpy(p_obj->p_plot, arr_lobj, sizeof(int) * LOBJ_W * LOBJ_H);
}
