# tests Makefile

include ../conf/conf.mk
CONF_INCL = ../conf/dep/include

simple_SRCS = simple_unitpass.cc simple_unitfail.cc
simple_OBJS = $(simple_SRCS:.cc=.o)
simple_TESTS = $(simple_SRCS:.cc=.t)

models_SRCS = models_atmos.cc
models_OBJS = $(models_SRCS:.cc=.o)
models_TESTS = $(models_SRCS:.cc=.t)

math_SRCS = math_cart_baseline.cc math_cart_mat33_baseline.cc \
	math_interpbilinear.cc
math_OBJS = $(math_SRCS:.cc=.o)
math_TESTS = $(math_SRCS:.cc=.t)

utils_SRCS = utils_time.cc utils_time_syscall.cc
utils_OBJS = $(utils_SRCS:.cc=.o)
utils_TESTS = $(utils_SRCS:.cc=.t)

TESTS = $(simple_TESTS) $(models_TESTS) $(math_TESTS) $(utils_TESTS)

LIBS += -lgtest -lgtest_main
$(math_TESTS) : LIBS += -lfmtkMath
math_LIBPATH = $(ENV_LIBPATH)=$(BUILDROOT)/conf/dep/lib
$(models_TESTS) : LIBS += -lfmtkModels
models_LIBPATH = $(ENV_LIBPATH)=$(BUILDROOT)/conf/dep/lib
$(utils_TESTS) : LIBS += -lfmtkUtils
utils_LIBPATH = $(ENV_LIBPATH)=$(BUILDROOT)/conf/dep/lib

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

tests_pass: tests_lvl1 tests_lvl2

tests_lvl1:
	./simple_unitpass.t
	$(models_LIBPATH) ./models_atmos.t
	$(math_LIBPATH) ./math_cart_baseline.t
	$(utils_LIBPATH) ./utils_time.t

tests_lvl2:
	$(math_LIBPATH) ./math_cart_mat33_baseline.t
	$(math_LIBPATH) ./math_interpbilinear.t
	$(utils_LIBPATH) ./utils_time_syscall.t

tests_fail:	# show what test failure looks like
	./simple_unitfail.t

clean:
	-rm -f *.o
	-rm -f $(TESTS)

$(utils_OBJS) : ${CONF_INCL}/utils/Timeval.h
$(math_OBJS) : ${CONF_INCL}/math/Cart3f.h \
	${CONF_INCL}/math/Cart3f_defn.h ${CONF_INCL}/math/Mat33f_defn.h
$(math_interp_OBJS) : ${CONF_INCL}/math/interpbilinear.h

