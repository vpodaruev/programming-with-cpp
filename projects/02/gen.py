#!/usr/bin/python3

import argparse
import random


parser = argparse.ArgumentParser(
    description="Generate test data for the least squares method:"
                " yi = a + b*xi + epsi")
parser.add_argument("a", type=float,
                    help="Constant coefficient in regression model")
parser.add_argument("b", type=float,
                    help="Linear coefficient in regression model")
parser.add_argument("-o", "--output", type=str, default="data.out",
                    help="Output filename [default: %(default)s]")
parser.add_argument("-e", "--epsilon", type=float, default=0.1,
                    help="Standard deviation of experiment error"
                         " [default: %(default)s]")
parser.add_argument("-n", type=int, default=50,
                    help="Number of experiment points [default: %(default)s]")
parser.add_argument("--x-range", nargs=2, type=float, default=[1.05, 2.95],
                    help="X-axis data range [default: %(default)s]")

args = parser.parse_args()


def y(x):
    return args.a + args.b*x + random.gauss(0., args.epsilon)


def my_range(x_range, n):
    h = (x_range[1] - x_range[0]) / n
    x = x_range[0]
    for i in range(n):
        yield x
        x += h


data = [f"{x:.6} {y(x):.6}" for x in my_range(args.x_range, args.n)]

with open(args.output, "w") as f:
    f.write("\n".join(data))
