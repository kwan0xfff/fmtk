# Makefile for models

include ../../conf/conf.mk

vpath %.h  ../../tksrc/src/models ../../conf/dep/include
vpath %.cc ../../tksrc/src/models

SRCS = Atmos.cc FlightVehicle.cc SimpleMotion.cc
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


