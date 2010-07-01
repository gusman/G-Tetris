CC = gcc
LN = gcc
CFLAGS = -Wall -pedantic -c
RM = del

OBJ_DIR = output-object
MODULE = main screen item board

sources :=
objects :=

include screen\screen.mk
include main\main.mk
include board\board.mk
include object\object.mk

all : $(objects)
	$(CC) $(objects) -o tetris.exe

clean:
	$(RM) $(objects)

%.o : %.c
	$(CC) $(CFLAGS) -I.  -c $< -o $@
