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

INFRA     := ./us_infra/
PRCS_MNG  := ./prcs_mng/

EXEC_DIR  := ./obj

MAIN_INCL  := ./incl/
INCL_PATH  := -I$(MAIN_INCL) -I$(INFRA) -I$(PRCS_MNG)

MAIN_SRC      := .

HDRS := 	$(wildcard $(MAIN_INCL)/*.h $(INFRA)/*.h $(PRCS_MNG)/*.h)
SRCS := 	$(wildcard $(MAIN_SRC)/*.c $(INFRA)/*.c $(PRCS_MNG)/*.c)
OBJS := 	$(SRCS:.c=.o)

#LIBS :=
#LPATH :=

EXEC := 	./$(EXEC_DIR)/exec

.PHONY: all 

# main target
all: $(EXEC_DIR) $(EXEC)

$(EXEC_DIR):
	@if [ ! -d ./$(EXEC_DIR) ]; then mkdir ./$(EXEC_DIR); fi;

$(EXEC): $(OBJS) Makefile
	$(CC_TOOL) $(OBJS) -o $(EXEC)

# target: header files dependecny
.c.o: *.c $(HDRS) Makefile
	$(CC_TOOL) $(CC_FLAG) $(INCL_PATH) $< -o $@

.PHONY: clean 
clean:
	rm $(OBJS)
	rm $(EXEC)



