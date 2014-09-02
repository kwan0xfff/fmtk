# Makefile for models

include ../../conf/conf.mk

vpath %.h  ../../tksrc/src/utils ../../conf/dep/include
vpath %.cc ../../tksrc/src/utils

SRCS = Timeval.cc Writer.cc
OBJS = $(SRCS:.cc=.o)

ifeq ($(KERNEL),Darwin)
    LDFLAGS += -dynamiclib
    LIBNAME = libfmtkUtils.dylib
endif
ifeq ($(KERNEL),Linux)
    LDFLAGS += -shared
    CXXFLAGS += -fPIC
    LIBNAME = libfmtkUtils.so
endif

all: $(LIBNAME)

$(LIBNAME): $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $@

clean:
	-rm -f *.o
	-rm -f $(LIBNAME)

Timeval.o : Timeval.h
Writer.o : Writer.h

