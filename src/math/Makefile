# Makefile for math

include ../../conf/conf.mk

vpath %.h  ../../tksrc/src/math ../../conf/dep/include
vpath %.cc ../../tksrc/src/math

SRCS = interpbilinear.cc rotate3f.cc
OBJS = $(SRCS:.cc=.o)

ifeq ($(KERNEL),Darwin)
    LDFLAGS += -dynamiclib
    LIBNAME = libfmtkMath.dylib
endif
ifeq ($(KERNEL),Linux)
    LDFLAGS += -shared
    CXXFLAGS += -fPIC
    LIBNAME = libfmtkMath.so
endif

all: $(LIBNAME)

$(LIBNAME): $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $@

clean:
	-rm -f *.o
	-rm -f $(LIBNAME)

interpbilinear.o : interpbilinear.h
rotate3f.o : rotate3f.h

