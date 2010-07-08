CC = gcc
LN = gcc
CFLAGS = -Wall -pedantic -I.
TARGET_FLAGS =

ifeq ($(TARGET), LINUX)
	RM = rm -rf
	TARGET_FLAGS = -D D_LINUX
else
	RM = del
endif

modules := screen/screen.mk main/main.mk board/board.mk object/object.mk
sources :=
objects :=

include $(modules)

all : $(objects)
	$(CC) $(CFLAGS) $(objects) -o tetris

clean:
ifeq ($(TARGET), LINUX)
	$(RM) $(objects)
else
	$(RM) $(subst /,\,$(objects))
endif

%.o : %.c
	$(CC) $(CFLAGS) $(TARGET_FLAGS) -c $< -o $@
