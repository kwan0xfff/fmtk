.. -*- restructuredtext -*-

Introduction
============

FMTK is a toolkit for flight modeling or flight mechanics.
At least, that is the general direction.

The build and target platforms are currently Mac OS X and Linux.
It is expected that platforms with a similar UNIX heritage would 
also be suitable.

FMTK provides an interface namespace for 3D Cartesian coordinate
computation (``cart3``).
The namespace may be implemented through a pure software solution, or
through hardware-specific SIMD intrinsics.

Currently, only a baseline software implementation of ``cart3`` is
provided.

To help maintain code quality, FMTK utilizes Google ``gtest`` to
implement a series of unit tests for C++.

