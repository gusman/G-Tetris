#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "object/object.h"
#include "object/object_o.h"

#define OOBJ_W	2
#define OOBJ_H	2

void oobj_genplot0(struct object_st *p_obj);
void oobj_genplot90(struct object_st *p_obj);
void oobj_genplot180(struct object_st *p_obj);
void oobj_genplot270(struct object_st *p_obj);
void oobj_genplot(struct object_st *p_obj);

void oobj_init(struct object_st *p_obj, unsigned int rot)
{
	p_obj->type = OBJECT_O;
	p_obj->rotation = rot;
	p_obj->pos_x = 0;
        p_obj->pos_y = 0;
	p_obj->width = OOBJ_W;
	p_obj->height = OOBJ_H;

        OBJECT_SETX(p_obj, 0);
        OBJECT_SETY(p_obj, 0);
        OBJECT_ROTATE(p_obj, DEGREE_90);

        free(p_obj->p_plot);
	p_obj->p_plot = (unsigned int *) malloc(sizeof(unsigned int) * (OOBJ_W * OOBJ_H));
        p_obj->pf_genplot = oobj_genplot;
}

void oobj_genplot(struct object_st *p_obj)
{
        switch(p_obj->rotation)
        {
                case DEGREE_0:
                        oobj_genplot0(p_obj);
                        break;

                case DEGREE_90:
                        oobj_genplot90(p_obj);
                        break;

                case DEGREE_180:
                        oobj_genplot180(p_obj);
                        break;

                case DEGREE_270:
                        oobj_genplot270(p_obj);
                        break;
        }
}


void oobj_genplot0(struct object_st *p_obj)
{
	unsigned int arr_oobj[OOBJ_H][OOBJ_W] = OROT_0;

        p_obj->width = OOBJ_W;
        p_obj->height = OOBJ_H;
        memcpy(p_obj->p_plot, arr_oobj, sizeof(int) * OOBJ_W * OOBJ_H);
}	

void oobj_genplot90(struct object_st *p_obj)
{
	unsigned int arr_oobj[OOBJ_W][OOBJ_H] = OROT_90;

        p_obj->width = OOBJ_H;
        p_obj->height = OOBJ_W;
        memcpy(p_obj->p_plot, arr_oobj, sizeof(int) * OOBJ_W * OOBJ_H);
}

void oobj_genplot180(struct object_st *p_obj)
{
	unsigned int arr_oobj[OOBJ_H][OOBJ_W] = OROT_180;

        p_obj->width = OOBJ_W;
        p_obj->height = OOBJ_H;
        memcpy(p_obj->p_plot, arr_oobj, sizeof(int) * OOBJ_W * OOBJ_H);
}

void oobj_genplot270(struct object_st *p_obj)
{
	unsigned int arr_oobj[OOBJ_W][OOBJ_H] = OROT_270;

        p_obj->width = OOBJ_H;
        p_obj->height = OOBJ_W;
        memcpy(p_obj->p_plot, arr_oobj, sizeof(int) * OOBJ_W * OOBJ_H);
}
