#!/usr/bin/env python3
#-*- coding: utf-8 -*-

"""FMTK high-level maintenance procedures
"""

import os, os.path
import sys
#import pdb              ### DEBUGGING

def add_dir(dirpath):
    """Make sure that directory 'dirpath' is available.
    Create it, if necessary.
    """
    if not os.path.exists(dirpath):
        os.makedirs(dirpath)
        print("Directory '%s' created." % dirpath)

def add_link(source, linkpath):
    """Create a symbolic link from conf/def to linkpath.
    """

    if os.path.exists(linkpath):
        print("file exists", linkpath)
    else:
        print("do link", source, "to", linkpath)
        os.symlink(source, linkpath)

def provide(spec):
    """Provide resouces according to spec."""

    paths = spec['paths']
    links = spec['links']

    add_dir(paths['build'])
    add_dir(paths['build'] + '/conf/dep')
    add_dir(paths['build'] + '/conf/dep/include')
    add_dir(paths['build'] + '/conf/dep/lib')

    deppath = paths['build'] + '/conf/dep'
    try:
        for linkname in links:
            src = links[linkname]
            add_link(src, deppath+'/'+linkname)
    except OSError as err:
        print ("linkname:", linkname)
        print ("OS error: {0}".format(err))
    except:
        print("Unexpected error:", sys.exc_info()[0])
        raise

# vim: set sw=4 tw=80 :
