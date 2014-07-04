# conf.mk

# Configuration parameters passed via GNU make
#

KERNEL = $(shell uname)
ifeq ($(KERNEL),Darwin)
    CXX := c++
    CXXFLAGS := -g -Wall -Werror -ffast-math
    LDFLAGS := -dynamiclib -lc++
    GTEST_DIR := $(HOME)/Tools/gtest
    ENV_LIBPATH = DYLD_LIBRARY_PATH
endif
ifeq ($(KERNEL),Linux)
    CXX := g++
    CXXFLAGS := -g -Wall -Werror
    LDFLAGS := -lstdc++
    ENV_LIBPATH = LD_LIBRARY_PATH
    GTEST_DIR := $(HOME)/Tools/gtest
endif
#BUILDROOT = /path/to/buildarea/root
#ifndef ($(BUILDROOT), undefined)
ifndef BUILDROOT
    $(info ** Define BUILDROOT in conf.mk or export from calling environment. **)
    $(error BUILDROOT is undefined)
endif

.SUFFIXES: .o .cc

.cc.o:
	$(CXX) $(CXXFLAGS) $(DEFNS) $(INCLS) -c $<

.o.:
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)


# USER DEFINED PATHS HERE
ifeq ($(KERNEL),Darwin)
    INCLS = -I/usr/local/include -I$(BUILDROOT)/conf/dep/include
    LIBS = -L/usr/local/lib -L$(BUILDROOT)/conf/dep/lib
endif
ifeq ($(KERNEL),Linux)
    INCLS = -I$(BUILDROOT)/conf/dep/include
    LIBS = -L$(BUILDROOT)/conf/dep/lib
endif


