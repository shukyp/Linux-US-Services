
# Variable

# true | false
dbg_info=false 

ifeq ($(dbg_info),true)
	DBG=-ggdb
else
	DBG=
endif

OBJ_FILES = main.o file1.o file2.o
HDR_FILES = file1.h file2.h

CMPLR_FLAG = -v -c -Wall $(DBG)
CC_TOOL = gcc 

EXECUTABLE = exec

# main target
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ_FILES) $(HDR_FILES)
	$(CC_TOOL) -o $(EXECUTABLE) $(OBJ_FILES)

# target: header files dependecny
*.o: *.c $(HDR_FILES)
	$(CC_TOOL) $(CMPLR_FLAG) *.c

.PHONY: clean cleanobj 

clean:
	rm *.o

cleanall:
	rm *.o
	rm $(EXECUTABLE)

