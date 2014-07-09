# sim1scenarios Makefile
#

include ../../conf/conf.mk
INCLS += -I..
LIBS += -L$(BUILDROOT)/conf/dep/lib -lfmtkModels -lfmtkMath -lfmtkUtils

MODULES=SimpleFlight

ifeq ($(KERNEL),Darwin)
    LDFLAGS = -dynamiclib
    CXXFLAGS += -ffast-math
endif
ifeq ($(KERNEL),Linux)
    CXXFLAGS += -ffast-math -fPIC
    LDFLAGS = -shared
endif
DLMODS=$(MODULES:=.$(DLSFX))

all: $(DLMODS) X15data.o

X15data.c : X15data.py
	python3 X15data.py > $@

$(DLMODS) : ../Scenario.h

clean:
	rm -f *.o
	rm -f X15data.c
	rm -f *.${DLSFX}
