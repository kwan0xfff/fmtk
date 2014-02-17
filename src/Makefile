# Makefile for models

include ../conf/conf.mk

SUBDIRS = models utils

all clean :
	for subdir in $(SUBDIRS); do \
	    ( cd $$subdir; ${MAKE} $@; ) \
	done

