# Makefile for models

include ../conf/conf.mk

SUBDIRS = math models utils

all clean :
	for subdir in $(SUBDIRS); do \
	    ${MAKE} -C $$subdir $@ || exit $$?; \
	done

