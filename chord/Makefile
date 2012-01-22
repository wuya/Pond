PROJECT			:= Pond
ROOT_PATH		:= /Users/kezl
PROJECT_PATH		:= $(ROOT_PATH)/$(PROJECT)

LIB_PATH		:= $(PROJECT_PATH)/lib

CHORD_PATH		:= $(PROJECT_PATH)/chord
CHORD_LIB		:=

BUILD_PATH		:= $(CHORD_PATH)/build

INCLUDE			= $(PROJECT_PATH)/include

CC				:= gcc
CFLAGS			:= -ggdb -Wall -Werror
CFLAGS			+= $(patsubst %,-I%,$(INCLUDE))
CFLAGS			+= -L$(LIB_PATH)

CHO_SRC			= $(CHORD_PATH)/chord.c\
				  $(CHORD_PATH)/hash.c\
				  $(CHORD_PATH)/main.c

CHO_OBJ 		= $(patsubst %.c,%.o,$(filter %.c,$(CHO_SRC)))

.PHONY : clean

all: mchord

mchord: $(CHO_OBJ)
	$(CC) $(CFLAGS) -o $(BUILD_PATH)/$@ $(CHO_OBJ) $(CHORD_LIB) ;

clean:
	rm -f $(CHORD_PATH)/*.{o,d}

hash:
	$(CC) $(CFLAGS) -o $(BUILD_PATH)/hash_test hash.c main.c

%.d: %.c
	$(CC) -MM $(CFLAGS) $*.c > $@

-include $(CHO_OBJ:.o=.d)

