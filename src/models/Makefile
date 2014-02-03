# Makefile for models

include ../../conf/conf.mk

SRCS = Atmos.cc
OBJS = $(SRCS:.cc=.o)

ifeq ($(KERNEL),Darwin)
    LDFLAGS += -dynamiclib
    LIBNAME = libfmtkModels.dylib
endif
ifeq ($(KERNEL),Linux)
    LDFLAGS += -shared
    CXXFLAGS += -fPIC
    LIBNAME = libfmtkModels.so
endif

all: $(LIBNAME)

stage1 : echobasics $(LIBNAME)
$(LIBNAME): $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $@

echobasics:
	echo $(shell uname)

clean:
	-rm -f *.o
	-rm -f $(LIBNAME)


