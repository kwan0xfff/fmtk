# cmds Makefile
# Applications initiated from command line.

include ../conf/conf.mk

vpath %.h  ../tksrc/cmds ../conf/dep/include
vpath %.cc ../tksrc/cmds

atmos_SRCS = atmostable.cc
atmos_OBJS = $(atmos_SRCS:.cc=.o)

#fltsim_SRCS = flightsim.cc
#fltsim_OBJS = $(fltsim_SRCS:.cc=.o)

EXCS = atmostable
SIM1 = libfmtkSim1.$(DLSFX)
SIM1SCEN = sim1scen.done
ifndef DLSFX
    $(info ** Define DLSFX in conf.mk or export from calling environment. **)
    $(info ** e.g., "so" or "dylib". **)
    $(error DLSFX is undefined)
endif

LIBS +=

atmostable : LIBS += -lfmtkModels

ENV = $(ENV_LIBPATH)=$(BUILDROOT)/conf/dep/lib

all: $(EXCS)

atmostable : atmostable.o
	$(CXX) $(CXXFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)

atmos: atmostable
	$(ENV) ./atmostable atmos.txt


clean:
	-rm -f *.o $(EXCS) *.${DLSFX}	# execution code
	-rm -f *.log atmos.txt		# runtime output
	-rm -f Makefile.dep

