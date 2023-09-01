#!/usr/bin/python3

"""Draw a curve from the experimental data.

Use experimental points and a computed linear regression coefficients
to make a plot. Save it in a PDF file.
"""

import argparse
import matplotlib.pyplot as plt
import pathlib


def read_data(infile):
    """Read an experimental data.

    Expected `infile` format is:
        x1 y1
        ...
        xN yN
    """
    with infile.open() as f:
        data = [[float(item) for item in line.split(maxsplit=1)]
                for line in f.readlines() if not line.isspace()]
        xx, yy = zip(*data)
        return xx, yy
    raise RuntimeError(f"Failed to read data from file ('{infile}')")


def compute_curve(xx, args):
    """Compute curve points using linear regression model."""
    def y(x):
        return args.a + args.b * x

    xe = [xx[0], xx[-1]]
    ye = [y(x) for x in xe]
    return xe, ye


def make_plot(points, curve, args):
    """Compose a figure."""
    plt.plot(*curve, "k")
    plt.plot(*points, "k+", markersize=8)
    plt.grid(True, which="both")
    plt.title(f"y = ({args.a} ± {args.da}) + ({args.b} ± {args.db})*x")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="Make a plot of the linear regression y=a+b*x"
                    "built from the data of an experiment")

    parser.add_argument("file", type=pathlib.Path,
                        help="file with experiment data")

    parser.add_argument("a", type=float,
                        help="estimate of the constant coefficient")
    parser.add_argument("da", type=float,
                        help="confidence band for `a`")

    parser.add_argument("b", type=float,
                        help="estimate of the linear coefficient")
    parser.add_argument("db", type=float,
                        help="confidence band for `b`")

    args = parser.parse_args()

    xx, yy = read_data(args.file)
    xe, ye = compute_curve(xx, args)
    make_plot((xx, yy), (xe, ye), args)

    plt.savefig(args.file.with_suffix(".pdf").name, bbox_inches="tight")
