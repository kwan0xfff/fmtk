# Makefile for models

include ../../conf/conf.mk
INCLS += -I.. -I../../tksrc/exptcmds

vpath %.h  ../../tksrc/exptcmds/sim1engine ../../conf/dep/include
vpath %.cc ../../tksrc/exptcmds/sim1engine

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


