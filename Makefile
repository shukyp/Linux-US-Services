#
# How depedency rule components are referred
#
# all: a.cpp b.cpp
# $@ mean to 'all' (the target)
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
dbginfo = true

ifeq ($(dbginfo),true)
	DBG=-ggdb
else
	DBG= 
endif

CC_FLAG := -v -Wall $(DBG) -c
CC_TOOL := gcc

ROOT_PATH      := .
INFRA_PATH     := ./us_infra
PRCS_MNG_PATH  := ./prcs_mng
EXEC_PATH  		:= ./obj

ROOT_INCL_PATH  := ./incl
INCL_PATH  := -I$(ROOT_INCL_PATH) -I$(INFRA_PATH) -I$(PRCS_MNG_PATH)

HDRS := 	$(wildcard $(ROOT_INCL_PATH)/*.h $(INFRA_PATH)/*.h $(PRCS_MNG_PATH)/*.h)
SRCS := 	$(wildcard $(ROOT_PATH)/*.c $(INFRA_PATH)/*.c $(PRCS_MNG_PATH)/*.c)
OBJS := 	$(SRCS:.c=.o)

#LIBS :=
#LPATH :=

EXEC := 	$(EXEC_PATH)/exec

.PHONY: all 

# main target
all: $(EXEC_PATH) $(EXEC)

$(EXEC_PATH):
	@if [ ! -d ./$(EXEC_PATH) ]; then mkdir ./$(EXEC_PATH); fi;

$(EXEC): $(OBJS) Makefile
	$(CC_TOOL) $(OBJS) -o $(EXEC)

# target: header files dependecny
#.c.o: $(HDRS) Makefile
%.o: %.c $(HDRS) Makefile 
	$(CC_TOOL) $(CC_FLAG) $(INCL_PATH) $< -o $@

#.SUFFIXES: .c .o

.PHONY: clean 
clean:
	rm $(OBJS)
	rm $(EXEC)



