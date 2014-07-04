# cmds Makefile
# Applications initiated from command line.

include ../conf/conf.mk
CONF_INCL = ../conf/dep/include

atmos_SRCS = atmostable.cc
atmos_OBJS = $(atmos_SRCS:.cc=.o)

fltsim_SRCS = flightsim.cc
fltsim_OBJS = $(fltsim_SRCS:.cc=.o)

EXCS = atmostable flightsim

LIBS +=

atmostable : LIBS += -lfmtkModels
flightsim : LIBS += -lfmtkModels -lfmtkMath

ENV = $(ENV_LIBPATH)=$(BUILDROOT)/conf/dep/lib

all: $(EXCS) # $(DLMODS)

atmostable : atmostable.o
	$(CXX) $(CXXFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)
flightsim : flightsim.o
	$(CXX) $(CXXFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)

atmos: atmostable
	$(ENV) ./atmostable atmos.txt

# flights: TBD -- example flight sim scenario

clean:
	-rm -f *.o $(EXCS)		# execution code
	-rm -f *.log atmos.txt		# runtime output
	-rm -f Makefile.dep

