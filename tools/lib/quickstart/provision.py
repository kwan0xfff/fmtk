#!/usr/bin/env python3
#-*- coding: utf-8 -*-

"""FMTK high-level maintenance procedures
"""

import os, os.path
import sys
import shutil
#import pdb              ### DEBUGGING

def add_dir(dirpath):
    """Make sure that directory 'dirpath' is available.
    Create it, if necessary.
    """
    dirpath = os.path.normpath(dirpath)
    if not os.path.exists(dirpath):
        os.makedirs(dirpath)
        print("Directory '%s' created." % dirpath)

def add_link(source, linkpath):
    """Create a symbolic link from conf/def to linkpath.
    """

    linkpath = os.path.normpath(linkpath)
    cwd = os.getcwd()
    if linkpath.endswith('tksrc'):
        linkdir = os.path.dirname(linkpath)
        if source in linkdir:
            source = os.path.relpath(source, linkdir)
    if cwd in linkpath:
        linkpath = os.path.relpath(linkpath, cwd)
    if os.path.exists(linkpath):
        print("file exists", linkpath)
    else:
        #print("Link", source, "to", linkpath)
        os.symlink(source, linkpath)

def provide(spec):
    """Provide resources according to spec."""

    paths = spec['paths']
    links = spec['links']

    if not paths['build'].startswith('/'):
        # Need build path to be absolute.
        paths['build'] = os.path.join (paths['fmtkroot'], paths['build'])
    add_dir(paths['build'])
    add_dir(paths['build'] + '/conf/dep')
    add_dir(paths['build'] + '/conf/dep/include')
    add_dir(paths['build'] + '/conf/dep/lib')

    deppath = paths['build'] + '/conf/dep'
    try:
        for linkname in links:
            src = links[linkname]
            add_link(src, deppath+'/'+linkname)
        add_link(paths['fmtkroot'], os.path.join(paths['build'],'tksrc'))
    except OSError as err:
        print ("linkname:", linkname)
        print ("OS error: {0}".format(err))
    except:
        print("Unexpected error:", sys.exc_info()[0])
        raise

    if os.path.normpath(paths['build']) == os.path.normpath(paths['fmtkroot']):
        return

    print("Copy makefiles")
    os.chdir(paths['fmtkroot'])
    pathbuild = paths['build']
    pathroot = paths['fmtkroot']
    topcomponents = ['conf', 'docs', 'src', 'tests', 'cmds']
    optionals = [ 'exptcmds', ]
    for candidate in optionals:
        if os.path.exists(candidate):
            topcomponents.append(candidate)
    topcomponents.append("Makefile")
    for component in topcomponents:
        for relpath, dirs, files in os.walk(component):
            for fname in ('Makefile', 'conf.mk'):
                if fname in files:
                    src = os.path.join(pathroot, relpath, fname)
                    trg = os.path.join(pathbuild, relpath, fname)
                    trgdir = os.path.join(pathbuild, relpath)
                    #print ('...', trg)
                    if not os.path.isdir(trgdir) and not os.path.exists(trgdir):
                        os.makedirs(trgdir)

                    shutil.copyfile(src, trg)
    fname = 'Makefile'  # get top-level Makefile
    src = os.path.join(pathroot, fname)
    trg = os.path.join(pathbuild, fname)
    #print ('...', trg)
    shutil.copyfile(src, trg)

    src = os.path.join(pathroot, "tools/bin/setbldenvrc")
    trg = os.path.join(pathbuild, "setbldenvrc")
    print ("copy setbldenvrc")
    shutil.copyfile(src, trg)


# vim: set sw=4 tw=80 :
