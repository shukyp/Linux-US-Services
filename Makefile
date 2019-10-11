#
# How depedency rule components are referred
#
# all: a.cpp b.cpp
# $@ mean to all
# $< a.cpp
# $^ a.cpp b.cpp
#
# ------------------------
#
# debug make file 
# make --debug[=flags]
#	no flags is like using -d
#	b basic debugging
# 	v verbose basic debugging
#	i show implicit rules
#	j detailed debug info
#	m show info while remaking makefile
#
# see: https://linux.die.net/man/1/make
#
#

# Variable

# true | false
dbg_info=false 

ifeq ($(dbg_info),true)
	DBG=-ggdb
else
	DBG=
endif

CC_FLAG := -v -Wall $(DBG) -c
CC_TOOL := gcc

MAIN_HDRDIR := 	./incl/
SS_HDRDIR := 	./incl2/
INCL_PATH := 	-I$(MAIN_HDRDIR) -I$(SS_HDRDIR)

EXEC_DIR := 	obj

#LIBS :=
#LPATH :=

MAIN_SRCDIR := 	.
SS_SRCDIR := 	./task

HDRS := 	$(wildcard $(MAIN_HDRDIR)/*.h $(SS_HDRDIR)/*.h)
SRCS := 	$(wildcard $(MAIN_SRCDIR)/*.c $(SS_SRCDIR)/*.c)
OBJS := 	$(SRCS:.c=.o)

EXEC := 	./$(EXEC_DIR)/exec

.PHONY: all 

# main target
all: $(EXEC_DIR) $(EXEC)

$(EXEC_DIR):
	@if [ ! -d ./$(EXEC_DIR) ]; then mkdir ./$(EXEC_DIR); fi;

$(EXEC): $(OBJS) 
	$(CC_TOOL) $(OBJS) -o $(EXEC)

# target: header files dependecny
.c.o: *.c $(HDRS)
	$(CC_TOOL) $(CC_FLAG) $(INCL_PATH) $<  -o $@

.PHONY: clean 
clean:
	rm $(OBJS)
	rm $(EXEC)



