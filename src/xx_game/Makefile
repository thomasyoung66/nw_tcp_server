
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
#      Created: 05/14/2015 04:43:06 PM CST 
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
CPP_EXTENSION  = cpp

# ------------  compiler  --------------------------------------------------------------
CC              = g++

# ------------  compiler flags  --------------------------------------------------------
#CFLAGS          = -Wall -O2         # Do optimize. Produce no debugging information.
CFLAGS          = -g -Wall -O3 -fPIC  -I../../os/include  -Wno-deprecated -Werror 

# ------------  linker-Flags  ----------------------------------------------------------
LFLAGS          = -L../../os/lib -g -lpthread -lrt  -lssl  -luv

# ------------  name of the executable  ------------------------------------------------
EXECUTABLE      = ./bin/xx_game

# ------------  list of all source files  ----------------------------------------------
C_SOURCES       = 

CPP_SOURCES     = main.cpp LoginEventHandler.cpp

STATIC_LIBS     = ../lib_app/libapp.a \
	../lib_net/libnet.a \
	../lib_util/libUtil.a \
	-llog4cxx -luv
#	../../os/lib/liblog4cxx.a 
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
	make -C ../lib_util
	make -C ../lib_net
	make -C ../lib_app
								$(CC) $(ALL_LFLAGS) -o $(EXECUTABLE) $(OBJECTS) $(STATIC_LIBS)
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
								rm  --force  $(EXECUTABLE)  *.o core.*
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
astyle:
	astyle --style=linux -t -y -p *.h *.cpp
	rm -rf *.orig
tag:
	 ctags *.* ../libutil/*.* ../tbnet/tbsys/src/*.* ../tbnet/tbnet/src/*.*  ../../snsapi/*.* ../libutil/json-c/*.*
release:
#	cp -rf  impush /home/micro_chat/impush/bin/.
#	svn commit -m "auto commit" /home/micro_chat/impush/bin
	cp -rf  impush /home/micro_chat_sd/impush/bin/.
	svn commit -m "auto commit" /home/micro_chat_sd/impush/bin
test:
	cp -rf  impush /home/micro_chat/impush/bin/.
	svn commit -m "auto commit" /home/micro_chat/impush/bin

# ======================================================================================
# vim: set tabstop=2: set shiftwidth=2: 
