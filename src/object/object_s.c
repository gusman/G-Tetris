#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "object/object.h"
#include "object/object_s.h"

#define SOBJ_W	3
#define SOBJ_H	2

void sobj_genplot0(struct object_st *p_obj);
void sobj_genplot90(struct object_st *p_obj);
void sobj_genplot180(struct object_st *p_obj);
void sobj_genplot270(struct object_st *p_obj);
void sobj_genplot(struct object_st *p_obj);

void sobj_init(struct object_st *p_obj, unsigned int rot)
{
	p_obj->type = OBJECT_S;
	p_obj->rotation = rot;
	p_obj->pos_x = 0;
        p_obj->pos_y = 0;
	p_obj->width = SOBJ_W;
	p_obj->height = SOBJ_H;

        OBJECT_SETX(p_obj, 0);
        OBJECT_SETY(p_obj, 0);
        OBJECT_ROTATE(p_obj, DEGREE_90);

        free(p_obj->p_plot);
	p_obj->p_plot = (unsigned int *) malloc(sizeof(unsigned int) * (SOBJ_W * SOBJ_H));
        p_obj->pf_genplot = sobj_genplot;
}

void sobj_genplot(struct object_st *p_obj)
{
        switch(p_obj->rotation)
        {
                case DEGREE_0:
                        sobj_genplot0(p_obj);
                        break;

                case DEGREE_90:
                        sobj_genplot90(p_obj);
                        break;

                case DEGREE_180:
                        sobj_genplot180(p_obj);
                        break;

                case DEGREE_270:
                        sobj_genplot270(p_obj);
                        break;
        }
}


void sobj_genplot0(struct object_st *p_obj)
{
	unsigned int arr_sobj[SOBJ_H][SOBJ_W] = SROT_0;

        p_obj->width = SOBJ_W;
        p_obj->height = SOBJ_H;
        memcpy(p_obj->p_plot, arr_sobj, sizeof(int) * SOBJ_W * SOBJ_H);
}	

void sobj_genplot90(struct object_st *p_obj)
{
	unsigned int arr_sobj[SOBJ_W][SOBJ_H] = SROT_90;

        p_obj->width = SOBJ_H;
        p_obj->height = SOBJ_W;
        memcpy(p_obj->p_plot, arr_sobj, sizeof(int) * SOBJ_W * SOBJ_H);
}

void sobj_genplot180(struct object_st *p_obj)
{
	unsigned int arr_sobj[SOBJ_H][SOBJ_W] = SROT_180;

        p_obj->width = SOBJ_W;
        p_obj->height = SOBJ_H;
        memcpy(p_obj->p_plot, arr_sobj, sizeof(int) * SOBJ_W * SOBJ_H);
}

void sobj_genplot270(struct object_st *p_obj)
{
	unsigned int arr_sobj[SOBJ_W][SOBJ_H] = SROT_270;

        p_obj->width = SOBJ_H;
        p_obj->height = SOBJ_W;
        memcpy(p_obj->p_plot, arr_sobj, sizeof(int) * SOBJ_W * SOBJ_H);
}
