#!/usr/bin/env python3
#-*- coding: utf-8 -*-

"""subst_cart3templ.py
Substitute values into a math "Cart3" template to produce a specific
implementation.

Used to provide float/double variants of some classes as an alternative
to traditional C++ template code.  (Potentially, this works reasonably
for C as well.)
"""

from string import Template
import sys

def subst3f(templ):
    "Produce text result of substituting Cart3f values in template tl."
    result = templ.substitute(ns='cart3',
        clasnm='Cart3f', CLASNM='CART3F', stype='float' )
    return result

def subst3d(templ):
    "Produce text result of substituting Cart3d values in template tl."
    result = templ.substitute(ns='cart3',
        clasnm='Cart3d', CLASNM='CART3D', stype='double' )
    return result

substfuncmap = {
    '3f': subst3f,
    '3d': subst3d
}

def main():
    pattern = sys.argv[1]
    fin = sys.argv[2]
    fout = sys.argv[3]

    if pattern in substfuncmap:
        func = substfuncmap[pattern]
    else:
        print('unknown pattern: '+pattern, file=sys.stderr)
        sys.exit(1)

    hin = open(fin, 'r')
    hout = open(fout, 'w')
    templ = Template(hin.read())
    trgtext = func(templ)

    hout.write(trgtext)

    hin.close()
    hout.close()

    sys.exit(0)

main()
# vim: set sw=4 tw=80 :
