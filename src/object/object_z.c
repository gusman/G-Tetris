#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "object/object.h"
#include "object/object_z.h"

#define ZOBJ_W	3
#define ZOBJ_H	2

void zobj_genplot0(struct object_st *p_obj);
void zobj_genplot90(struct object_st *p_obj);
void zobj_genplot180(struct object_st *p_obj);
void zobj_genplot270(struct object_st *p_obj);
void zobj_genplot(struct object_st *p_obj);

void zobj_init(struct object_st *p_obj, unsigned int rot)
{
	p_obj->type = OBJECT_Z;
	p_obj->rotation = rot;
	p_obj->pos_x = 0;
        p_obj->pos_y = 0;
	p_obj->width = ZOBJ_W;
	p_obj->height = ZOBJ_H;

        OBJECT_SETX(p_obj, 0);
        OBJECT_SETY(p_obj, 0);
        OBJECT_ROTATE(p_obj, DEGREE_90);

        free(p_obj->p_plot);
	p_obj->p_plot = (unsigned int *) malloc(sizeof(unsigned int) * (ZOBJ_W * ZOBJ_H));
        p_obj->pf_genplot = zobj_genplot;
}

void zobj_genplot(struct object_st *p_obj)
{
        switch(p_obj->rotation)
        {
                case DEGREE_0:
                        zobj_genplot0(p_obj);
                        break;

                case DEGREE_90:
                        zobj_genplot90(p_obj);
                        break;

                case DEGREE_180:
                        zobj_genplot180(p_obj);
                        break;

                case DEGREE_270:
                        zobj_genplot270(p_obj);
                        break;
        }
}


void zobj_genplot0(struct object_st *p_obj)
{
	unsigned int arr_zobj[ZOBJ_H][ZOBJ_W] = ZROT_0;

        p_obj->width = ZOBJ_W;
        p_obj->height = ZOBJ_H;
        memcpy(p_obj->p_plot, arr_zobj, sizeof(int) * ZOBJ_W * ZOBJ_H);
}	

void zobj_genplot90(struct object_st *p_obj)
{
	unsigned int arr_zobj[ZOBJ_W][ZOBJ_H] = ZROT_90;

        p_obj->width = ZOBJ_H;
        p_obj->height = ZOBJ_W;
        memcpy(p_obj->p_plot, arr_zobj, sizeof(int) * ZOBJ_W * ZOBJ_H);
}

void zobj_genplot180(struct object_st *p_obj)
{
	unsigned int arr_zobj[ZOBJ_H][ZOBJ_W] = ZROT_180;

        p_obj->width = ZOBJ_W;
        p_obj->height = ZOBJ_H;
        memcpy(p_obj->p_plot, arr_zobj, sizeof(int) * ZOBJ_W * ZOBJ_H);
}

void zobj_genplot270(struct object_st *p_obj)
{
	unsigned int arr_zobj[ZOBJ_W][ZOBJ_H] = ZROT_270;

        p_obj->width = ZOBJ_H;
        p_obj->height = ZOBJ_W;
        memcpy(p_obj->p_plot, arr_zobj, sizeof(int) * ZOBJ_W * ZOBJ_H);
}
