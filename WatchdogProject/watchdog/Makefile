
# make clean/all CONFIG=Debug/Release ARCH=linux64/raspi ECHO=0/1

# the parrent dir of "arch" dir
ROOT_DIR = ../..

PROJ_SRCS = $(wildcard *.c)
#PROJ_SRCS = aaa.c bbb.cpp

# list of directories containing header files
PROJ_INC_DIR = $(ROOT_DIR)/ds/vector\
$(ROOT_DIR)/system_programming/uid\
$(ROOT_DIR)/ds/heap\
$(ROOT_DIR)/ds/pqueue\
$(ROOT_DIR)/ds/scheduler\

# the executable file
PROJ_OUT = client.out

# list of compiler flags (prepended with "-" sign)
#PROJ_CFLAGS = -Wunused-but-set-variable
PROJ_CFLAGS =
PROJ_CPPFLAGS =

#PROJ_MACROS = _BSD_SOURCE
PROJ_MACROS =

# additional object files (created by other projects)
PROJ_ADD_OBJS = uid.o vector.o heapify.o heap.o pqueue.o scheduler.o

# additional libraries
PROJ_LIBS =

# linker flags
PROJ_LDFLAGS = -lpthread

# list of projects (makefiles) this project depends on
PROJ_DEPENDS =

include $(ROOT_DIR)/make/Project.mak
