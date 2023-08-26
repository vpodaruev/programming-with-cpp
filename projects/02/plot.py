#!/usr/bin/python3

import argparse, pathlib

## set the command line interface
parser = argparse.ArgumentParser (description="""
  Make a plot of the linear regression y=a+b*x
  built from the data of an experiment""")

parser.add_argument ("file", type=pathlib.Path,
  help="file with experiment data")

parser.add_argument ("a", type=float,
  help="estimate of the constant coefficient")
parser.add_argument ("da", type=float,
  help="confidence band for `a`")

parser.add_argument ("b", type=float,
  help="estimate of the linear coefficient")
parser.add_argument ("db", type=float,
  help="confidence band for `b`")


args = parser.parse_args()


## read an experiment data;
## supposed file format is:
##   x1 y1
##   ...
##   xN yN
xx, yy = None, None
with args.file.open() as f :
  data = [[float(item) for item in line.split (maxsplit=2)]
          for line in f.readlines() if not line.isspace()]
  xx, yy = zip (*data)


## set the regression shape
y = lambda x : args.a + args.b*x

## compute points of the regression curve
xe = [xx[0], xx[-1]]
ye = [y(x) for x in xe]


import matplotlib.pyplot as plt

## make figure
plt.plot (xe, ye, "k")
plt.plot (xx, yy, "k+", markersize=8)

plt.grid (True, which="both")
plt.title ("y = ({} ± {}) + ({} ± {})*x"
           .format (args.a, args.da, args.b, args.db))

plt.savefig (args.file.with_suffix(".pdf").as_posix(), bbox_inches="tight")
