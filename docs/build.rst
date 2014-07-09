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
  * GCC 4.6.x or 4.7.x (Ubuntu)

To use the ``fmtk-qs`` quick-start script, you will also need:

* Python 3

See below under *Workarounds and special notes* for guidance on the
script.

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

Quick-start
-----------

A quick-start script ``tools/fmtk-qs``, written in Python 3,
is being developed to help quickly get a usable build environment started.

It is intended to enable builds in a separate directory,
but this is not quite there yet.
At the moment, builds work reliably in the original source tree.

To use it, at the top of the source tree:

* Put in a symlink from ``tksrc`` to the current directory, e.g., ::

    $ ln -s . tksrc

* Find the Google c++ test framework ("gtest") root,
  determine the shared library type (``dylib`` or ``so``).
  Then create the dependency tree using ``tools/fmtk-qs`` doing something like::

    $ ./tools/fmtk-qs -q -r $(pwd) -g ${GTEST}/include -G ${GTEST}/lib -s dylib

  Without ``-q``, the script will allow you to interactively enter the values.

  Each symlink is listed as it is created.  You may see a "File exists" error.
  It may be from running the command a second time.  In general, this should be safe.
  But to be clean, get rid of the subdirectory ``conf/dep``.

* Export BUILDROOT as current directory (top of source tree), and
  DLSFX as dynamic library suffix ("so" or "dylib"). ::

    $ export BUILDROOT=$(pwd)
    $ export DYSFX="so"

* Build it. ::

    $ make

* Run the tests.  This is a quick way to get familiar with what is in the toolkit. ::

    $ ( cd tests; make tests)

  If all goes well, the tests all passed.
  Of course, in development, usually that's not the case.

  You can check out some sample and skeletal programs in the ``cmds`` directory.
  The ``atmostable`` command is driven by ``make atmos``.
  The ``flightsim`` command is very skeletal; is driven ``make flight1``.

And now, on to debugging...
