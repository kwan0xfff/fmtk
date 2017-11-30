# exptcmds Makefile
# Experimental applications initiated from command line.

include ../conf/conf.mk

vpath %.h  ../tksrc/exptcmds ../conf/dep/include
vpath %.cc ../tksrc/exptcmds

fltsim_SRCS = flightsim.cc
fltsim_OBJS = $(fltsim_SRCS:.cc=.o)

EXCS = flightsim
SIM1 = libfmtkSim1.$(DLSFX)
SIM1SCEN = sim1scen.done
ifndef DLSFX
    $(info ** Define DLSFX in conf.mk or export from calling environment. **)
    $(info ** e.g., "so" or "dylib". **)
    $(error DLSFX is undefined)
endif

LIBS +=

flightsim : LIBS += -L. -lfmtkSim1 -lfmtkModels -lfmtkUtils -ldl

ENV = $(ENV_LIBPATH)=$(BUILDROOT)/conf/dep/lib

all: $(EXCS) $(SIM1) $(SIM1SCEN)

run: drop1

flightsim : flightsim.o $(SIM1)
	$(CXX) $(CXXFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)

$(SIM1) :
	${MAKE} -C sim1engine -e DLSFX=${DLSFX} ${SIM1} || exit $$?
	ln -s sim1engine/${SIM1}

$(SIM1SCEN) :
	${MAKE} -C sim1scenarios all || exit $$?
	touch $(SIM1SCEN)

drop1: flightsim SimpleDrop.${DLSFX}
	$(ENV):. ./flightsim SimpleDrop

SimpleDrop.${DLSFX} :
	[ -e SimpleDrop.${DLSFX} ] || ln -s sim1scenarios/SimpleDrop.${DLSFX}

clean:
	-rm -f *.o $(EXCS) *.${DLSFX}	# execution code
	-rm -f *.log atmos.txt		# runtime output
	-rm -f Makefile.dep

