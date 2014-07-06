# cmds Makefile
# Applications initiated from command line.

include ../conf/conf.mk

atmos_SRCS = atmostable.cc
atmos_OBJS = $(atmos_SRCS:.cc=.o)

fltsim_SRCS = flightsim.cc
fltsim_OBJS = $(fltsim_SRCS:.cc=.o)

EXCS = atmostable flightsim
SIM1 = libfmtkSim1.$(DLSFX)
SIM1SCEN = sim1scen.done
ifndef DLSFX
    $(info ** Define DLSFX in conf.mk or export from calling environment. **)
    $(info ** e.g., "so" or "dylib". **)
    $(error DLSFX is undefined)
endif

LIBS +=

atmostable : LIBS += -lfmtkModels
flightsim : LIBS += -L. -lfmtkSim1 -lfmtkModels -lfmtkMath -lfmtkUtils -ldl

ENV = $(ENV_LIBPATH)=$(BUILDROOT)/conf/dep/lib

all: $(EXCS) $(SIM1) $(SIM1SCEN)

atmostable : atmostable.o
	$(CXX) $(CXXFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)
flightsim : flightsim.o $(SIM1)
	$(CXX) $(CXXFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)

$(SIM1) :
	${MAKE} -C sim1engine -e DLSFX=${DLSFX} ${SIM1} || exit $$?
	ln -s sim1engine/${SIM1}

$(SIM1SCEN) :
	${MAKE} -C sim1scenarios all || exit $$?
	touch $(SIM1SCEN)

atmos: atmostable
	$(ENV) ./atmostable atmos.txt


flight1:
	[ -e SimpleFlight.${DLSFX} ] || ln -s sim1scenarios/SimpleFlight.${DLSFX}
	$(ENV):. ./flightsim SimpleFlight

clean:
	-rm -f *.o $(EXCS) *.${DLSFX}	# execution code
	-rm -f *.log atmos.txt		# runtime output
	-rm -f Makefile.dep $(SIM1) ${SIM1SCEN}
	make -C sim1engine clean
	make -C sim1scenarios clean

