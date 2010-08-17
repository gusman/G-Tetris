#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "object/object.h"
#include "object/object_i.h"

#define IOBJ_W	4
#define IOBJ_H	1

void iobj_genplot0(struct object_st *p_obj);
void iobj_genplot90(struct object_st *p_obj);
void iobj_genplot180(struct object_st *p_obj);
void iobj_genplot270(struct object_st *p_obj);
void iobj_genplot(struct object_st *p_obj);

void iobj_init(struct object_st *p_obj, unsigned int rot)
{
	p_obj->type = OBJECT_I;
	p_obj->rotation = rot;
	p_obj->pos_x = 0;
        p_obj->pos_y = 0;
	p_obj->width = IOBJ_W;
	p_obj->height = IOBJ_H;

        OBJECT_SETX(p_obj, 0);
        OBJECT_SETY(p_obj, 0);
        OBJECT_ROTATE(p_obj, DEGREE_90);

        free(p_obj->p_plot);
	p_obj->p_plot = (unsigned int *) malloc(sizeof(unsigned int) * (IOBJ_W * IOBJ_H));
        p_obj->pf_genplot = iobj_genplot;
}

void iobj_genplot(struct object_st *p_obj)
{
        switch(p_obj->rotation)
        {
                case DEGREE_0:
                        iobj_genplot0(p_obj);
                        break;

                case DEGREE_90:
                        iobj_genplot90(p_obj);
                        break;

                case DEGREE_180:
                        iobj_genplot180(p_obj);
                        break;

                case DEGREE_270:
                        iobj_genplot270(p_obj);
                        break;
        }
}


void iobj_genplot0(struct object_st *p_obj)
{
	unsigned int arr_iobj[IOBJ_H][IOBJ_W] = IROT_0;

        p_obj->width = IOBJ_W;
        p_obj->height = IOBJ_H;
        memcpy(p_obj->p_plot, arr_iobj, sizeof(int) * IOBJ_W * IOBJ_H);
}	

void iobj_genplot90(struct object_st *p_obj)
{
	unsigned int arr_iobj[IOBJ_W][IOBJ_H] = IROT_90;

        p_obj->width = IOBJ_H;
        p_obj->height = IOBJ_W;
        memcpy(p_obj->p_plot, arr_iobj, sizeof(int) * IOBJ_W * IOBJ_H);
}

void iobj_genplot180(struct object_st *p_obj)
{
	unsigned int arr_iobj[IOBJ_H][IOBJ_W] = IROT_180;

        p_obj->width = IOBJ_W;
        p_obj->height = IOBJ_H;
        memcpy(p_obj->p_plot, arr_iobj, sizeof(int) * IOBJ_W * IOBJ_H);
}

void iobj_genplot270(struct object_st *p_obj)
{
	unsigned int arr_iobj[IOBJ_W][IOBJ_H] = IROT_270;

        p_obj->width = IOBJ_H;
        p_obj->height = IOBJ_W;
        memcpy(p_obj->p_plot, arr_iobj, sizeof(int) * IOBJ_W * IOBJ_H);
}
