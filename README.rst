.. -*- restructuredtext -*-

===============
README for FMTK
===============

FMTK is a toolkit for flight modeling or flight mechanics,
written principally in C++.
At least, that is the general direction.
It is developed with the idea that computational flight hardware
in the near future will take advantage of widely accepted advances
in compilers and computer architecture such as *SIMD intrinsics*.

The build and target platforms are currently Mac OS X and Linux.
It is expected that platforms with a similar UNIX heritage would 
also be suitable.

Major components currently include:

* Cartesian 3D vector library (single precision), with provision for SIMD
  intrinsics.
* "Timeval" wrapper to POSIX struct timeval for execution time
  measurement.
* Test suite using the Google Test framework for C++.

License
=======

Source code of FMTK is distributed under the Apache License, Version 2.0,
January 2004.  (http://www.apache.org/licenses/)

Documentation
=============

There is currently limited documentation, found in `docs`_.
The introduction, in `docs/intro`_, gives the rationale for the project,
a high-level roadmap, and a bit about what to expect of the source code.
Some guidance on building is provided in `docs/build`_ 


.. _docs: docs
.. _docs/intro: docs/intro.html
.. _docs/build: docs/build.html

