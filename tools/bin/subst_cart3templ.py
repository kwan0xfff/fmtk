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

def substv3f(templ):
    "Produce text result of substituting Cart3f values in template tl."
    result = templ.substitute(
        ns='cart3', clasnm='Cart3f', CLASNM='CART3F',
        stype='float',
        sdesc='IEEE single precision floating point',
    )
    return result

def substv3d(templ):
    "Produce text result of substituting Cart3d values in template tl."
    result = templ.substitute(
        ns='cart3', clasnm='Cart3d', CLASNM='CART3D',
        stype='double',
        sdesc='IEEE double precision floating point',
    )
    return result

def substm3f(templ):
    "Produce text result of substituting Mat33f values in template tl."
    result = templ.substitute(
        ns='cart3', clasnm='Mat33f', CLASNM='MAT33F',
        stype='float', vtype='Cart3f',
        sdesc='IEEE single precision floating point',
    )
    return result

def substm3d(templ):
    "Produce text result of substituting Mat33d values in template tl."
    result = templ.substitute(
        ns='cart3', clasnm='Mat33d', CLASNM='MAT33D',
        stype='double', vtype='Cart3d',
        sdesc='IEEE double precision floating point',
    )
    return result

substfuncmap = {
    'v3f': substv3f,
    'v3d': substv3d,
    'm3f': substm3f,
    'm3d': substm3d,
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
