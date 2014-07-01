.. -*- restructuredtext -*-

Introduction
============

FMTK is a toolkit for flight modeling or flight mechanics (FM or FM).
At least, that is the general direction.

The two target application environments of the toolkit:

  * virtual flight environments for design or modeling of flight vehicles
  * avionics guidance, navigation, and control (GNC) systems

Ideally, the core computational parts of the toolkit can be used in both.
Thus, the core code that models the flight environment becomes part of
the flight vehicle.

Eventually, parts of the code may need to satisfy safety and reliability
certifications.
Users may include experimenters building small UAVs or satellites as
well as expert vehicle and avionics designers.
Because these type of projects pose concerns for the uninvolved public
as well as project participants,
technical interest groups and government agencies have established or
are developing guidelines and standards to protect the interests of
these parties.


Roadmap
-------

The build and target platforms are currently Mac OS X and Linux.
It is expected that platforms with a similar UNIX heritage would 
also be suitable.

Eventually, the target environment should 32-bit real-time operating systems
that support a POSIX API.
Possible examples include: Linux 3.x, Linux 3.x with Xenomai, RTEMS.
The hardness or softness of the real-time demand is up to the platform integrator.

While multi-processor and multi-thread support are not specific features of
the toolkit, it is assumed that FMTK will have to run efficiently in that
sort of environment.


Source code
-----------

Because size (mass) and power consumption matter to small flight vehicles,
the overall memory footprint of RTOS and application code and efficiency of
computation matter in how the code is crafted.

Some of the coding strategy is at odds with accepted practice in
major parts of the real-time embedded community.
The FMTK code attempts to be mindful of these concerns and the reasons
behind them.

The code is written in C++.
In the minds of some, this is asking for unconstrained trouble where
the cost or size of computation cannot be adequately controlled.
FMTK is being developed with these costs in mind.
Key C++ features which are used:

  * *operator overloading* -- used to bring clarity to certain frequently
    used mathematical constructs, particularly vector and matrix
    computations.

  * *templates* -- used on a limited basis.  Some generic collections
    (maps, lists) simply must be used in a reliable mobile system.
    It is not clear that hand-crafting such code provides significant
    benefit over the existing container template classes.

FMTK provides an interface namespace for 3D Cartesian coordinate
computation (``cart3``).
The namespace may be implemented through a pure software solution, or
through hardware-specific SIMD intrinsics.

Currently, only a baseline software implementation of ``cart3`` is
provided.

To help maintain code quality, FMTK utilizes Google ``gtest`` to
implement a series of unit tests for C++.

