
#===============================================================================
#
#     Filename: Makefile
#  Description: 
#
#        Usage: make              (generate executable                       )
#               make clean        (remove objects, executables, prerequisits )
#               make tarball      (generate compressed archive               )
#               make zip          (generate compressed archive               )
#
#      Version: 1.0
#      Created: 03/23/2016 05:52:18 PM CST 
#     Revision: ---
#
#       Author: YangLiuShun (Thomas Young)
#      Company: www.movnow.com
#        Email: yangliushun@movnow.com 
#
#        Notes: Prerequisites are generated automatically; makedepend is not 
#               needed (see documentation for GNU make Version 3.79, April 2000,
#               section 4.12). The utility sed and BASH file tests are used.
#               
#===============================================================================

# ------------  C++ file name extensions  ----------------------------------------------
CPP_EXTENSION  = cc

# ------------  compiler  --------------------------------------------------------------
CC              = g++

# ------------  compiler flags  --------------------------------------------------------
#CFLAGS          = -Wall -O2         # Do optimize. Produce no debugging information.
CFLAGS          = -O2 -g  -I../../third_party/libuv-v1.9.1/include/    # Do not optimize. Produce debugging information.
#CFLAGS          = -Wall -O2 -g  -I../../third_party/libuv-v1.9.1/include/    # Do not optimize. Produce debugging information.

# ------------  linker-Flags  ----------------------------------------------------------
LFLAGS          = -g -lssl -L../../third_party/libuv-v1.9.1/.libs/ -lrt

# ------------  name of the executable  ------------------------------------------------
EXECUTABLE      = main

# ------------  list of all source files  ----------------------------------------------
C_SOURCES       = main.c

CPP_SOURCES     = 

# ------------  additional system include directories  ---------------------------------
GLOBAL_INC_DIR  = 

# ------------  additional system library directories  ---------------------------------
GLOBAL_LIB_DIR  = 

# ------------  system libraries  ------------------------------------------------------
SYS_LIBS        = -lm  

# ------------  private include directories  -------------------------------------------
LOCAL_INC_DIR   = .

# ------------  private library directories  -------------------------------------------
LOCAL_LIB_DIR   = .

# ------------  private libraries  -----------------------------------------------------
LOCAL_LIBS      = 

# ------------  archive generation -----------------------------------------------------
TARBALL_EXCLUDE = *.{o,gz,zip}
ZIP_EXCLUDE     = *.o *.gz *.zip

#=======================================================================================
# The following statements usually need not to be changed
#=======================================================================================

ALL_INC_DIR     = $(LOCAL_INC_DIR) $(GLOBAL_INC_DIR)
ALL_LIB_DIR     = $(LOCAL_LIB_DIR) $(GLOBAL_LIB_DIR)
ALL_CFLAGS      = $(CFLAGS)  -I$(ALL_INC_DIR)
ALL_LFLAGS      = $(LFLAGS)  -L$(ALL_LIB_DIR) $(SYS_LIBS) $(LOCAL_LIBS)

# ------------  generate the names of the object files  --------------------------------
OBJECTS         = ${C_SOURCES:.c=.o} 
OBJECTS        += $(CPP_SOURCES:.$(CPP_EXTENSION)=.o)

# ------------  generate the names of the hidden prerequisite files  -------------------
PREREQUISITES   = $(addprefix .,${C_SOURCES:.c=.d} )
PREREQUISITES  += $(addprefix .,${CPP_SOURCES:.$(CPP_EXTENSION)=.d} )

# ------------  make the executable  ---------------------------------------------------
$(EXECUTABLE):	$(OBJECTS)
								$(CC) $(ALL_LFLAGS) -o $(EXECUTABLE) $(OBJECTS) ../../third_party/libuv-v1.9.1/.libs/libuv.a
#								./$(EXECUTABLE)

# ------------  list of the automatically generated prerequisites  ---------------------
#include         $(PREREQUISITES)

# ------------  make the objects  ------------------------------------------------------
%.o:						%.c
								$(CC) -c $(ALL_CFLAGS) $< 

%.o:						%.$(CPP_EXTENSION)
								$(CC) -c $(ALL_CFLAGS) $< 

# ------------  make the prerequisites  ------------------------------------------------
#  echoing of the sed command is suppressed by the leading @
#
.%.d:           %.c
								@set -e; $(CC)  -MM $< \
								| sed 's/\($*\)\.o[ :]*/\1.o $@ : /g' > $@; \
								[ -s $@ ] || rm -f $@
								@[ -f $@ ]&& echo "prerequisite file  $@  generated"

.%.d:           %.$(CPP_EXTENSION)
								@set -e; $(CC)  -MM $< \
								| sed 's/\($*\)\.o[ :]*/\1.o $@ : /g' > $@; \
								[ -s $@ ] || rm -f $@
								@[ -f $@ ]&& echo "prerequisite file  $@  generated"

# ------------  remove generated files  ------------------------------------------------
# ------------  remove hidden backup files  --------------------------------------------
clean:
							rm -rf core.*
								rm  --force  $(EXECUTABLE) *.o
								rm  --force  *~

# ------------ tarball generation ------------------------------------------------------
tarball:
					lokaldir=`pwd`; lokaldir=$${lokaldir##*/}; \
					rm --force $$lokaldir.tar.gz;              \
					tar --exclude=$(TARBALL_EXCLUDE)           \
					    --create                               \
					    --gzip                                 \
					    --verbose                              \
					    --file  $$lokaldir.tar.gz *

# ------------ zip ---------------------------------------------------------------------
zip:
					lokaldir=`pwd`; lokaldir=$${lokaldir##*/}; \
					zip -r  $$lokaldir.zip * -x $(ZIP_EXCLUDE)
tag:
	 ctags * ../../third_party/libuv-v1.9.1/include/* ../../third_party/libuv-v1.9.1/src/*
# ======================================================================================
# vim: set tabstop=2: set shiftwidth=2: 
