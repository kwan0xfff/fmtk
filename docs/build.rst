.. -*- restructuredtext -*-

Building FMTK
=============

FMTK depends on a number of external tools and libraries to build and test.

Configuration to host a build is centralized in the top-level
``conf`` directory.
This include includes:

* ``conf.mk`` - configuration settings which are used by GNU Make.
* ``dep`` directory - a directory tree to resolve dependencies to
  external header files and libraries.
  These are typically resolved as symbolic links, but may optionally be
  complete source trees.

Caveat: Dreams
--------------

Ultimately, the intent is to cross-build FMTK from a host development
system to a variety of embedded of POSIX-based target systems or
application environments.
However, this is not the case today.

As a result, various of the build system may ultimately be
re-written to allow multi-target builds.

Toolchain
---------

Build and test of FMTK uses tools that are readily available for:

* Mac OS X 10.9 (Mavericks)
* Ubuntu 12.04 (Precise Penguin)

Fundmentally, this breaks down to the following tools:

* GNU Make - make 3.81
* Compiler toolchain -- one of

  * Apple LLVM 5.1 (Mac OS X)
  * GCC 4.6.2 (Ubuntu)

External libraries
------------------

`Google C++ Testing Framework <http://code.google.com/p/googletest>`_
is utilized to build C++ unit tests for FMTK.

Configuration for ``Make``
--------------------------

The ``conf.mk`` file is included by makefiles in FMTK.
It uses the ``uname`` shell command to determine the OS kernel,
and thus the build and run parameters.

The file includes a section for user-defined paths.
If you develop on different host systems, this may be useful for
distinguishing the different paths that they use for libraries and header files.
Alternatively, a lot of components may be resolved through the ``conf/dep``
subdirectory.

Dependency tree
---------------

The ``conf/dep`` subdirectory allows symlinks to be made to various
external libraries.
This allows the number of separate include and library path flags
(``-I`` and ``-L``) to be reduced.

Candidates for the tree include:

* ``include/gtest`` - Google test framework header files directory
* ``lib/libgtest.a``, ``lib/libgtest.a`` -- Google test framework libraries

In early development, to support the unit tests, is useful to link
the models header files and library.
For example, ``lib/libfmtkModels.dylib`` may point to the build of the
fmtkModels library, which includes simple atmospheric modeling.  This
particular location is specific to Mac OS X; a different naming convention
involving ``.so`` files is used on Linux systems.

In addition, the ``include/models`` may point to the models
directory so that header files such as ``Atmos.h`` can be found.

To exercise the ``math/cart3`` code,
``include/math`` may point to the ``math`` directory.

A later version of the build system will including deployment of libraries
and header files into a staging area.

Manual build
------------

Currently, there is no global build directory.  The recommended
course of action is:

* Set up the dependency tree.  Download the necessary libraries if
  you don't already have them.
* Build the models library.  From the root of this project tree::

    $ cd src/models; make

* Build and run the tests.  From the root of this project tree::

    $ cd tests; make tests


Workarounds and Special Notes
=============================

A quick-start script ``tools/fmtk-qs`` is being developed to help quickly
get a usable build environment started.
It is intended to enable builds in a separate directory.
Within the build directory, ``tksrc`` would be a symlink to the source code.

This is quite working.
At the moment, builds work reliably in the original source tree.
To make this work, at the top of the source tree:

* Rename ``tksrc`` to something else like ``tksrc-orig``, e.g., ::

    $ mv tksrc tksrc-orig

* Find the Google c++ test framework ("gtest") root, determine the shared library type.
  Then create the dependency tree using ``tools/fmtk-qs`` doing something like::

    $ ./tools/fmtk-qs -q -r $(pwd) -g $(GTEST)/include -G $(GTEST)/lib -s dylib

  Without ``-q``, the script will allow you to interactively enter the values.

* Build it. ::

    $ make


