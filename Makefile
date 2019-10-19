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

# Config Variables

# true | false
dbginfo = true

ifeq ($(dbginfo),true)
	DBG			:=-ggdb
else
	DBG			:=
endif

CC_FLAG 			:= -v -Wall $(DBG) -c
CC_TOOL 			:= gcc

#common settings
MAIN_INCL		:= ./incl
EXEC_PATH  		:= ./obj
LIB_PATH 		:= $(EXEC_PATH)

EXECUTABLE 		:= $(EXEC_PATH)/exec

#US_INFRA (root) module
US_INFRA			:= us_infra
US_INFRA_PATH	:= ./$(US_INFRA)
US_INFRA_LIB	:= $(LIB_PATH)/lib_$(US_INFRA).a

#PRCS_MNG module
PRCS_MNG			:= prcs_mng
PRCS_MNG_PATH	:= ./$(PRCS_MNG)
PRCS_MNG_LIB	:= $(LIB_PATH)/lib_$(PRCS_MNG).a

MDL_LIBS			:= $(US_INFRA_LIB) $(PRCS_MNG_LIB)

# main target
.PHONY: all
all: $(EXEC_PATH) $(EXECUTABLE)
	@echo __ALL__ $(EXEC_PATH) $(EXECUTABLE)

# target: assures the folder for the exetuable exist
$(EXEC_PATH):
	@echo __EXEC_PATH__
	@if [ ! -d $(EXEC_PATH) ]; then mkdir $(EXEC_PATH); fi;

# executable file target
$(EXECUTABLE): $(MDL_LIBS) Makefile
	@echo __EXECUTABLE__ $(MDL_LIBS)
	$(CC_TOOL) -static $(MDL_LIBS) -o $(EXECUTABLE)

$(US_INFRA_LIB): $(wildcard $(US_INFRA_PATH)/*.h $(US_INFRA_PATH)/*.c $(MAIN_INCL)/*.h)
	@echo __US_INFRA_LIB__
	make -C $(US_INFRA_PATH) _DBG_=$(DBG) -f MakefileInfra

$(PRCS_MNG_LIB): $(wildcard $(PRCS_MNG_PATH)/*.h $(PRCS_MNG_PATH)/*.c $(MAIN_INCL)/*.h)
	@echo __PRCS_MNG_LIB__
	make -C $(PRCS_MNG_PATH) _DBG_=$(DBG) -f MakefilePrcsMng

.PHONY: clean 
clean:
	make clean -C $(US_INFRA) _DBG_=$(DBG) -f MakefileInfra
	make clean -C $(PRCS_MNG) _DBG_=$(DBG) -f MakefilePrcsMng
	@if [ -f $(EXECUTABLE) ]; then rm $(EXECUTABLE); fi;

