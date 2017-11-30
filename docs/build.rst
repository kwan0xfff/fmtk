.. -*- restructuredtext -*-

Building FMTK
=============

FMTK is designed to allow building of executables for the host system
or for separate architectures, application environments, or other or diagnostic builds.

It depends on a number of external tools and libraries to build and test.
Configuration to host a build is centralized in the top-level
``conf`` directory of a target build tree.
This include includes:

* ``conf.mk`` - configuration settings which are used by GNU Make.
* ``dep`` directory - a directory tree to resolve dependencies to
  external header files and libraries.
  These are typically resolved as symbolic links, but may optionally be
  complete source trees.

A quick-start script ``fmtk-qs`` is available to handle much of the configuration.
(See "Manual Build" and "Quick-start" below.)

Toolchain
---------

Build and test of FMTK on the host system uses tools that are readily available for:

* Mac OS X 10.9 (Mavericks)
* Ubuntu 12.04 (Precise Penguin)

Fundmentally, this breaks down to the following tools:

* GNU Make - make 3.81
* Compiler toolchain -- one of

  * Apple LLVM 5.1 (Mac OS X) (latest test: 9.0.0)
  * GCC 4.6.x or 4.7.x (Ubuntu)

Configuring the target build tree is supported by ``fmtk-qs``.
To use it, you will need:

* Python 3

To use Mac OS X or Linux as host for cross-builds to a different hardware targets,
different toolchains should be used.
The preferred toolchain is often specified by the supplier of the hardware target.

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

Currently, it includes:

* ``include/gtest`` - Google test framework header files directory
* ``lib/libgtest.a``, ``lib/libgtest.a`` -- Google test framework libraries

In early development, to support the unit tests, it is useful to link to
the models header files and library.
For example, ``lib/libfmtkModels.dylib`` may point to the build of the
fmtkModels library, which includes simple atmospheric modeling.
A different naming convention involving ``.so`` files is used on Linux systems.

In addition, the ``include/models`` may point to the models
directory so that header files such as ``Atmos.h`` can be found.

To exercise the ``math/cart3`` code,
``include/math`` may point to the ``math`` directory.

Manual build
------------

The quick-start script ``tools/fmtk-qs`` is designed configure the build tree.
When executables are built for the host system, it can be used to rapidly
set up the build tree.

Things to do:

* Download the necessary libraries if you don't already have them.

* Interactively, configure a build tree. ::

    $ ./tools/fmtk-qs

  For ``Target build path``, enter ``.`` to build in the source tree,
  or for the more adverturous, ``build`` to build in a separate build tree.
  For ``Cart3d implementation``: choose ``baseline``.  (More details below.)

* Define key environment variables.
  Very likely you will need to define ``BUILDROOT`` and ``DLSFX``.
  At the top of newly generated build tree, you can set::

    $ export BUILDROOT=$(pwd)

  The dynamic library suffix ``DLSFX`` should be set to the ``so`` or
  ``dylib``, depending on your target platform. For example, ::

    $ export DLSFX=dylib   # macOS

* Build everything.  Go to the build diretory, and then...::

    $ make

* Run the unit tests.  From the root of build tree::

    $ ( cd tests; make tests )

  If all went well, everything passed.

* Build and run the simple command-line applications.
  From the root of build tree tree::

    $ cd cmds
    $ make atmos            # generate a standard atmosphere tble
    $ cat atmos.txt         # show the table
    $ diff refdata/atmos-ref.txt atmos.txt
                            # list any differences from golden reference
    # path to ref might need to go through ../tksrc/cmds; hence:
    # diff ../tksrc/cmds/refdata/atmos-ref.txt atmos.txt

* To see an simple trajectory, go to 'exptcmds' directory.
  Then build and try it out::

    $ cd $BUILDROOT/exptcmds
    $ make run              # runs drop test (no aero)
    $ cat SimpleDrop.log    # drop trajectory

Quick-start
-----------

The quick-start script ``tools/fmtk-qs``, written in Python 3,
is designed to help quickly get a usable build environment started.

* We'll assume here that the libraries and executables will go into
  a new subdirectory named ``build``.  Set this up first. ::

    $ mkdir build
    $ cd build

* Find the Google C++ test framework ("gtest") root,
  determine the shared library type (``dylib`` or ``so``).
  Then create the dependency tree using ``tools/fmtk-qs`` ::

    $ ../tools/fmtk-qs -q -r $(pwd) -g ${GTEST}/include -G ${GTEST}/lib -s dylib

  Without ``-q``, the script will allow you to interactively enter the values.

  Each symlink is listed as it is created.  You may see a "File exists" error.
  It may be from running the command a second time.  In general, this should be safe.
  But to be clean, get rid of the subdirectory ``conf/dep``.

* Export BUILDROOT as current directory (top of source tree), and
  DLSFX as dynamic library suffix ("so" or "dylib"). ::

    $ export BUILDROOT=$(pwd)
    $ export DLSFX="so"

``fmtk-qs`` creates a symlink ``tksrc`` to point from the root of the build tree
(``BUILDROOT``) to the root of the source tree.
This link is used as an element of many of the dependencies and makefiles.

Workarounds and Special Notes
=============================

* Currently, the ``fmtk-qs -q`` option does not specify a ``Cart3d`` implementation.
  It simply uses ``baseline``.
  In fact, there is no special code for other implementations yet (e.g., SIMD),
  and compiler technology may ultimately prove these to be unnecessary.
