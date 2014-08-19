# Makefile for models

include ../../conf/conf.mk
INCLS += -I..

SRCS = SimEngine.cc
OBJS = $(SRCS:.cc=.o)

ifeq ($(KERNEL),Darwin)
    LIBS += -lfmtkUtils -lfmtkModels
    LDFLAGS += -dynamiclib ${LIBS}
    LIBNAME = libfmtkSim1.dylib
endif
ifeq ($(KERNEL),Linux)
    LDFLAGS += -shared
    CXXFLAGS += -fPIC
    LIBNAME = libfmtkSim1.so
endif
CXXFLAGS += -DDLSFX=\"${DLSFX}\"

all: $(LIBNAME)

$(LIBNAME): $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $@

clean:
	-rm -f *.o
	-rm -f $(LIBNAME)


