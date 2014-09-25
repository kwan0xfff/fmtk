#!/usr/bin/env python
#-*- coding: utf-8 -*-

import sys
import re

data = """
Some data from X-15

Estimated from graphs in Figure 7 of:
    title: Summary of Full-Scale Lift and Drag Characteristics of the X-15 Airplane
    authors:  Saltzman, Edwin J.; Garringer, Darwin J.
    date:  March 1966
    serial: NASA TN D-3343

Mach    cLift   alpha   cDrag
Mach    cLift   deg     cDrag

0.65    0.0     1.0     0.065
0.65    0.2     4.0     0.075
0.65    0.4     6.5     0.10
0.65    0.5     8.25    0.13

0.72    0.1     2.5     0.07
0.72    0.2     4.0     0.075
0.72    0.4     7.0     0.10
0.72    0.55    9.5     0.135

0.89    0.1     2.0     0.07
0.89    0.2     3.5     0.075
0.89    0.4     6.0     0.105
0.89    0.6     9.5     0.165
0.89    0.8     14.0    0.28

1.1     0.15    3.0     0.125
1.1     0.2     4.0     0.13
1.1     0.4     7.0     0.16
1.1     0.6     10.5    0.22
1.1     0.8     15.0    0.31
1.1     1.0     19.0    0.48

1.2     0.1     1.5     0.07
1.2     0.2     4.0     0.075
1.2     0.4     7.5     0.165
1.2     0.6     10.0    0.22
1.2     0.8     16.0    0.32
1.2     1.0     19.0    0.45

1.4     0.1     2.0     0.10
1.4     0.2     4.0     0.12
1.4     0.4     7.0     0.15
1.4     0.6     11.0    0.24
1.4     0.8     16.0    0.32

1.6     0.1     2.0     0.095
1.6     0.2     3.5     0.10
1.6     0.4     8.0     0.16
1.6     0.6     12.0    0.24

2.4     0.0     1.0     0.07
2.4     0.2     5.0     0.09
2.4     0.4     10.0    0.18

2.9     0.0     1.5     0.06
2.9     0.1     3.5     0.07
2.9     0.2     6.0     0.09
2.9     0.3     9.5     0.12

3.3     0.0     2.0     0.055
3.3     0.1     5.0     0.07
3.3     0.2     8.0     0.09
3.3     0.3     12.0    0.14
3.3     0.4     16.0    0.20

3.7     0.0     2.0     0.05
3.7     0.1     5.5     0.06
3.7     0.2     9.0     0.09
3.7     0.3     12.0    0.13
3.7     0.4     16.0    0.20

4.1     0.0     3.0     0.045
4.1     0.1     7.0     0.06
4.1     0.2     11.0    0.09
4.1     0.3     14.0    0.13
4.1     0.4     18.0    0.20
"""

preamble = """\
lift and drag coefficients
look-up by Mach and angle of attack
ordering:  Mach,  angAttack, cLift, cDrag\
"""

print("const float x15data_liftdrag[][4] = {")

linecount = 0

limit = 4

for line in preamble.split('\n'):
    print("\t//", line)

for line in data.split('\n'):
    if len(line) == 0:
        continue
    if not line[0].isdigit():
        continue

    items = re.split('\s+', line.strip())
    if len(items)!=4:
        print >>sys.stderr, "wrong number of items"
        print("wrong number of items", file=sys.stderr)
        sys.exit(1)
    mach, cLift, aAttack, cDrag = items
    print('\t{', mach+'f,', aAttack+'f,', cLift+'f,', cDrag+'f },')
    linecount += 1


print("};  // x15data")
print("const int x15data_nLines =", linecount, ";")
print()

# vim: set sw=4 tw=80 :
