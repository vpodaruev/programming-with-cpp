#!/usr/bin/python3

import argparse
import math
import matplotlib as mpl
import pathlib

from matplotlib import pyplot as plt


# set the command line interface
parser = argparse.ArgumentParser(
    description="""Make a plot from a file with two column data""")

parser.add_argument("file", type=pathlib.Path,
                    help="file with data")

args = parser.parse_args()


# read data;
# supposed file format is:
#   x1 y1
#   ...
#   xN yN
xx, yy = None, None
with args.file.open() as f:
    data = [[float(item) for item in line.split(maxsplit=2)]
            for line in f.readlines() if not line.isspace()]
    xx, yy = zip(*data)


# set the temperature shape
ave = 10.
amplitude = 5.
phase = 6. - 14
day_hours = 24


def y(x):
    return ave + amplitude * math.sin(2*math.pi * (x + phase)/day_hours)


# compute points of the regression curve
n_max = 100
xe = [x * day_hours/n_max for x in range(0, n_max)]
ye = [y(x) for x in xe]


# make figure
mpl.rcParams['font.size'] = 14

plt.figure(figsize=(18, 4))
plt.plot(xe, ye, "k--")
plt.plot(xx, yy, "k+", markersize=8)

plt.grid(True, which="both")

plt.savefig(args.file.with_suffix(".pdf").as_posix(), bbox_inches="tight")
