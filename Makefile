# Makefile for FMTK
# This makefile is intended for use in the target build environment.
#

SUBDIRS = src tests cmds

all clean : conf_targets
	for subdir in $(SUBDIRS); do \
	    ( cd $$subdir; ${MAKE} $@; ) \
	done

conf_targets : conf/dep/include conf/dep/lib

conf/dep/include conf/dep/lib :
	@echo Build requires conf/conf.mk and associated symlinks.
	@echo You may find tools/fmtk-qs handy for a quick start.
	@echo Also...
	@echo Create a symlink \"tksrc\" from the build tree to the source tree.
	@exit 1

dotests :
	cd tests; ${MAKE} tests


