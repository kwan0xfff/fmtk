#!/usr/bin/env python3
#-*- coding: utf-8 -*-

"""FMTK high-level maintenance procedures
"""

import os, os.path
import sys
from getopt import getopt, GetoptError
from .provision import provide

#import pdb

def findpathwithchild(pathlist, childpath, limit=None):
    """Find a path from pathlist which has childpath underneath it.
    For example, '/this/path/lib/has' may have 'src/models' beneath 'lib'.
    The return value would be '/this/path/lib'.
    The maximum number of parent directories to set is set by 'limit'.
    """
    #print ("pathlist", pathlist)
    childpath = os.path.normpath(childpath)
    for climbingpath in pathlist:
        here = os.path.normpath(climbingpath + '/.')
        for _n in range(limit):
            possible = here + '/' + childpath
            if os.path.exists(possible):
                return here             # found it
            here = os.path.dirname(here)

def providedir(dirpath):
    """Make sure that directory 'dirpath' is available.
    Create it, if necessary.
    """
    if not os.path.exists(dirpath):
        os.makedirs(dirpath)
        print("Directory '%s' created." % dirpath)

def add_local_dep(confspec):
    "Add local project relative paths."

    links = confspec['links']
    links['include/math'] = "../../../tksrc/src/math"
    links['include/models'] = "../../../tksrc/src/models"
    links['include/utils'] = "../../../tksrc/src/utils"

    so_suffix = confspec['so-suffix']
    for module in ('Models', 'Utils'):
        lib_so = 'libfmtk%s.%s' % (module, so_suffix)
        subdir = module.lower()
        links['lib/' + lib_so] = "../../../src/%s/%s" % (subdir, lib_so)

def parseargs(argv, spec):
    """Parse optional command line args 'argv' and load into config spec
    dictionary 'spec'.
    """

    paths = spec['paths']
    links = spec['links']

    try:
        (opts, args) = getopt(argv[1:], 'r:g:G:s:m:hq',
            ['buildroot', 'gtestinclude', 'gtestlib',
             'so-suffix', 'mathimpl', 'help', 'quick'])
    except GetoptError as ex:
        #print ("error: %s" % str(ex), file=sys.stderr)
        sys.exit(1)

    for opt, arg in opts:
        if   opt == '-r' or opt == '--buildroot':
            paths['build'] = arg
        elif opt == '-g' or opt == '--gtestinclude':
            links['include/gtest'] = arg + '/gtest'
        elif opt == '-G' or opt == '--gtestlib':
            libpath = arg
            for lib in ('libgtest.a', 'libgtest_main.a'):
                links['lib/' + lib] = libpath + '/' + lib
        elif opt == '-s' or opt == '--so-suffix':
            spec['so-suffix'] = arg
        #elif opt == '-m' or opt == '--mathimpl':
        #    spec['cart3mpl-'] = arg
        elif opt == '-h' or opt == '--help':
            spec['help'] = True
        elif opt == '-q' or opt == '--quick':
            spec['quick'] = True


def query(confspec):
    "Interactive query for values."

    paths = confspec['paths']
    links = confspec['links']

    print ("Please enter values for the following settings.")
    print ("(Press Enter to accept a default, if available.)")

    # Target build path
    # default = paths['fmtkroot'] + '/build'    # proper default
    default = paths['fmtkroot']                 # workaround
    response = input('Target build path (%s): ' % default)
    paths['build'] = (response, default)[response=='']
    #print ('path:', paths['build'])

    # GTest paths
    print ('Google C++ test framework (GTest) paths')
    inclpath = input('GTest include (above gtest/gtest.h): ')
    links['include/gtest'] = inclpath + '/gtest'
    libpath = input('GTest lib (above libgtest.a): ')
    for lib in ('libgtest.a', 'libgtest_main.a'):
        links['lib/' + lib] = libpath + '/' + lib

    # Target OS (shared library suffix, etc.)
    print ("Shared library/object suffix, e.g.: dylib, so")
    confspec['so-suffix'] = input('shared object suffix: ')

    # Target Cart3 math implementation
    # not yet
    print ("Cart3 math implementation; one of: " "baseline, sse2, msa, altivec, neon")
    confspec['cart3-impl'] = input('Cart3 implementation: ')

    add_local_dep(confspec)
    provide(confspec)           # do it


def quickstart(argv):
    """Main quick start routine.
    If using "-q", run something like:
        fmtk-qs -q -r $(SRCTOP) -g $(GTEST)/include -G $(GTEST)/lib -s dylib
    Otherwise, just enter command and add values interactively.
    """

    confspec = {}
    confspec['paths'] = paths = {}
    confspec['links'] = links = {}

    print ("Welcome to FMTK quickstart.")
    paths['fmtkroot'] = findpathwithchild(
        (os.path.abspath('.'),), 'src/models', 3)
    print ("root path discovered at", paths['fmtkroot'])
    parseargs(argv, confspec)
    if ('quick' not in confspec):
        query(confspec)

    add_local_dep(confspec)
    provide(confspec)           # do it

    return 0




# vim: set sw=4 tw=80 :
