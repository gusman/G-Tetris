CC = gcc
LN = gcc
CFLAGS = -Wall -pedantic -I.
CURSES_FLAGS :=
TARGET_FLAGS :=


ifeq ($(TARGET), LINUX)
	RM = rm -rf
	TARGET_FLAGS = -D D_LINUX
	CURSES_FLAGS = -lncurses
else
	RM = rm -rf
	CURSES_FLAGS = -lpdcurses
endif

modules := screen/screen.mk main/main.mk board/board.mk object/object.mk
sources :=
objects :=

include $(modules)

all : $(objects)
	$(CC) $(objects) -o tetris $(CURSES_FLAGS) $(CFLAGS)

clean:
	$(RM) $(objects)

%.o : %.c
	$(CC) -c $< -o $@ $(CFLAGS)  $(TARGET_FLAGS) $(CURSES_FLAGS)
