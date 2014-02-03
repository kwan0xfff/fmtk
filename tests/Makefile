# tests Makefile

include ../conf/conf.mk

simple_SRCS = simple_unitpass.cc simple_unitfail.cc
simple_OBJS = $(simple_SRCS:.cc=.o)
simple_TESTS = $(simple_SRCS:.cc=.t)

models_SRCS = models_atmos.cc
models_OBJS = $(models_SRCS:.cc=.o)
models_TESTS = $(models_SRCS:.cc=.t)

math_SRCS = math_cart_baseline.cc
math_OBJS = $(math_SRCS:.cc=.o)
math_TESTS = $(math_SRCS:.cc=.t)

TESTS = $(simple_TESTS) $(models_TESTS) $(math_TESTS)

LIBS += -lgtest -lgtest_main
$(models_TESTS) : LIBS += -lfmtkModels
models_LIBPATH = $(ENV_LIBPATH)=$(FMTKROOT)/conf/dep/lib

LDFLAGS =

CXXFLAGS += -g -Wall -Wextra
# On Mavericks, no '-pthread'
ifeq ($(KERNEL),Linux)
    LDFLAGS += -pthread
endif

.SUFFIXES: .t
.o.t :
	$(CXX) $(CXXFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)

all: $(TESTS)

tests: $(TESTS) tests_pass

tests_pass:
	./simple_unitpass.t
	$(models_LIBPATH) ./models_atmos.t
	./math_cart_baseline.t

tests_fail:	# show what test failure looks like
	./simple_unitfail.t

clean:
	-rm -f *.o
	-rm -f $(TESTS)

