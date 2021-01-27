
# make clean/all CONFIG=Debug/Release ARCH=linux64/raspi ECHO=0/1

# the parrent dir of "arch" dir
ROOT_DIR = ../../../../

PROJ_SRCS = $(wildcard *.cpp)\
			$(wildcard $(ROOT_DIR)/projects/silver_lining/src/*.cpp)
#PROJ_SRCS = silver_lining_v01.cpp

# list of directories containing header files
PROJ_INC_DIR = $(ROOT_DIR)/projects/silver_lining/include\
			   $(ROOT_DIR)/projects/silver_lining/include/slave

# the executable file
PROJ_OUT = slave_app.out

# list of compiler flags (prepended with "-" sign)
#PROJ_CFLAGS = -Wunused-but-set-variable
PROJ_CFLAGS =
PROJ_CPPFLAGS = -std=c++11

#PROJ_MACROS = _BSD_SOURCE
PROJ_MACROS =

# additional object files (created by other projects)
PROJ_ADD_OBJS =

# additional libraries
PROJ_LIBS = $(ROOT_DIR)/projects/silver_lining/lib/libglobals.so

# linker flags
PROJ_LDFLAGS = -pthread -ldl

# list of projects (makefiles) this project depends on
PROJ_DEPENDS  =

include $(ROOT_DIR)/make/Project.mak
