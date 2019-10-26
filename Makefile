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
EXEC_PATH  		:= ./bin
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

#PRCS_SCHED module
PRCS_SCHED		:= prcs_sched
PRCS_SCHED_PATH:= ./$(PRCS_SCHED)
PRCS_SCHED_LIB	:= $(LIB_PATH)/lib_$(PRCS_SCHED).a

#PRCS_IPCITC module
PRCS_IPCITC		:= prcs_ipcitc
PRCS_IPCITC_PATH:= ./$(PRCS_IPCITC)
PRCS_IPCITC_LIB	:= $(LIB_PATH)/lib_$(PRCS_IPCITC).a

MDL_LIBS			:= $(US_INFRA_LIB) $(PRCS_MNG_LIB) $(PRCS_SCHED_LIB) $(PRCS_IPCITC_LIB)

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

$(PRCS_SCHED_LIB): $(wildcard $(PRCS_SCHED_PATH)/*.h $(PRCS_SCHED_PATH)/*.c $(MAIN_INCL)/*.h)
	@echo __PRCS_SCHED_LIB__
	make -C $(PRCS_SCHED_PATH) _DBG_=$(DBG) -f MakefilePrcsSched	

$(PRCS_IPCITC_LIB): $(wildcard $(PRCS_IPCITC_PATH)/*.h $(PRCS_IPCITC_PATH)/*.c $(MAIN_INCL)/*.h)
	@echo __PRCS_IPCITC_LIB__
	make -C $(PRCS_IPCITC_PATH) _DBG_=$(DBG) -f MakefilePrcsIpcItc
	
.PHONY: clean 
clean:
	make clean -C $(US_INFRA) _DBG_=$(DBG) -f MakefileInfra
	make clean -C $(PRCS_MNG) _DBG_=$(DBG) -f MakefilePrcsMng
	make clean -C $(PRCS_SCHED) _DBG_=$(DBG) -f MakefilePrcsSched
	make clean -C $(PRCS_IPCITC) _DBG_=$(DBG) -f MakefileIpcItc
	@if [ -f $(EXECUTABLE) ]; then rm $(EXECUTABLE); fi;

