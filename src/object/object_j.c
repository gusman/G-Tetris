#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "object/object.h"
#include "object/object_j.h"

#define JOBJ_W	3
#define JOBJ_H	2

void jobj_genplot0(struct object_st *p_obj);
void jobj_genplot90(struct object_st *p_obj);
void jobj_genplot180(struct object_st *p_obj);
void jobj_genplot270(struct object_st *p_obj);
void jobj_genplot(struct object_st *p_obj);

void jobj_init(struct object_st *p_obj, unsigned int rot)
{
	p_obj->type = OBJECT_J;
	p_obj->rotation = rot;
	p_obj->pos_x = 0;
        p_obj->pos_y = 0;
	p_obj->width = JOBJ_W;
	p_obj->height = JOBJ_H;

        OBJECT_SETX(p_obj, 0);
        OBJECT_SETY(p_obj, 0);
        OBJECT_ROTATE(p_obj, DEGREE_90);

        free(p_obj->p_plot);
	p_obj->p_plot = (unsigned int *) malloc(sizeof(unsigned int) * (JOBJ_W * JOBJ_H));
        p_obj->pf_genplot = jobj_genplot;
}

void jobj_genplot(struct object_st *p_obj)
{
        switch(p_obj->rotation)
        {
                case DEGREE_0:
                        jobj_genplot0(p_obj);
                        break;

                case DEGREE_90:
                        jobj_genplot90(p_obj);
                        break;

                case DEGREE_180:
                        jobj_genplot180(p_obj);
                        break;

                case DEGREE_270:
                        jobj_genplot270(p_obj);
                        break;
        }
}


void jobj_genplot0(struct object_st *p_obj)
{
	unsigned int arr_jobj[JOBJ_H][JOBJ_W] = JROT_0;

        p_obj->width = JOBJ_W;
        p_obj->height = JOBJ_H;
        memcpy(p_obj->p_plot, arr_jobj, sizeof(int) * JOBJ_W * JOBJ_H);
}	

void jobj_genplot90(struct object_st *p_obj)
{
	unsigned int arr_jobj[JOBJ_W][JOBJ_H] = JROT_90;

        p_obj->width = JOBJ_H;
        p_obj->height = JOBJ_W;
        memcpy(p_obj->p_plot, arr_jobj, sizeof(int) * JOBJ_W * JOBJ_H);
}

void jobj_genplot180(struct object_st *p_obj)
{
	unsigned int arr_jobj[JOBJ_H][JOBJ_W] = JROT_180;

        p_obj->width = JOBJ_W;
        p_obj->height = JOBJ_H;
        memcpy(p_obj->p_plot, arr_jobj, sizeof(int) * JOBJ_W * JOBJ_H);
}

void jobj_genplot270(struct object_st *p_obj)
{
	unsigned int arr_jobj[JOBJ_W][JOBJ_H] = JROT_270;

        p_obj->width = JOBJ_H;
        p_obj->height = JOBJ_W;
        memcpy(p_obj->p_plot, arr_jobj, sizeof(int) * JOBJ_W * JOBJ_H);
}
