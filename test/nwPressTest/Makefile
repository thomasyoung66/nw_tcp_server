
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
#      Created: 07/05/2017 07:02:19 PM PDT 
#     Revision: ---
#
#       Author: YangLiuShun (Thomas Young)
#      Company: no name company
#        Email: 65619882@qq.com
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
CFLAGS          = -Wall -O0 -g  -I../../os/include/    # Do not optimize. Produce debugging information.

# ------------  linker-Flags  ----------------------------------------------------------
LFLAGS          = -g

# ------------  name of the executable  ------------------------------------------------
EXECUTABLE      = main

# ------------  list of all source files  ----------------------------------------------
C_SOURCES       = 

CPP_SOURCES     = main.cpp

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
								$(CC) $(ALL_LFLAGS) -o $(EXECUTABLE) $(OBJECTS) ../../os/lib/libuv.a -lpthread
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

# ======================================================================================
# vim: set tabstop=2: set shiftwidth=2: 
