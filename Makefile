# Makefile for FMTK
# This makefile is intended for use in the target build environment.
#

SUBDIRS = src tests

all clean : conf_targets
	for subdir in $(SUBDIRS); do \
	    ( cd $$subdir; ${MAKE} $@; ) \
	done

conf_targets : conf/dep/include conf/dep/lib

conf/dep/include conf/dep/lib :
	@echo Build requires conf/conf.mk and associated symlinks.
	@echo You may find tools/fmtk-qs handy for a quick start.
	@exit 1
