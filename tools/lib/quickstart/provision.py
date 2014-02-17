#!/usr/bin/env python3
#-*- coding: utf-8 -*-

"""FMTK high-level maintenance procedures
"""

import os, os.path

def add_dir(dirpath):
    """Make sure that directory 'dirpath' is available.
    Create it, if necessary.
    """
    if not os.path.exists(dirpath):
        os.makedirs(dirpath)
        print ("Directory '%s' created." % dirpath)

def add_link(source, linkpath):
    """Create a symbolic link from conf/def to linkpath.
    """

    if not os.path.exists(linkpath):
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
    for linkname in links:
        src = links[linkname]
        add_link(src, deppath+'/'+linkname)


# vim: set sw=4 tw=80 :
