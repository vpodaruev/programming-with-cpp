#!/usr/bin/python3

import math
import re


rubicon = 0.6  # the minimum positive level of the knowledge


def value(s):
    try:
        return float(s)
    except ValueError:
        pass
    return 0.


def name(s):
    if s.startswith('*'):
        return r"\textbf{" + s[1:] + "}"
    elif s.startswith('+'):
        return r"\textsl{" + s[1:] + "}"
    return s


def name_short(s):
    surname, *other = [item for item in s.split()]
    return name(surname + " " + ".".join(
        [word[0] for word in other if not word.isspace()]) + ".")


def lang(s):
    langs = s.split(',')
    if 2 < len(langs):
        s = ", ".join(langs[:1] + [r"\ldots"])
    return r"\texttt{\small " + s.replace('#', r'\#') + "}"


def test(s):
    try:
        ntask, score = s.split('/', maxsplit=1)
        return ntask + "/" + r"\textbf{" + score + "}"
    except ValueError:
        return s


def ctrl(s):
    try:
        ntask, score = s.split('/', maxsplit=1)
        return value(score), ntask + "/" + r"\textbf{" + score + "}"
    except ValueError:
        return 0., s


def task(s):
    def numrepl(m):
        try:
            int(m.group(1))
            return r"\:\mbox{\scriptsize\fbox{" + m.group(1) + r"}}\:"
        except ValueError:
            return ""

    s = re.sub(r"([0-9]+)", numrepl, s)

    syms = [c.strip() for c in s.split()]
    smap = {
        '+':  (1., r'\(+\)'),
        '+.': (1., r'\pd'),
        '+-': (.5, r'\(\pm\)'),
        '-+': (.5, r'\(\mp\)'),
        '-.': (0., r'\md'),
        '-':  (0., r'\(-\)')
    }
    score = sum([smap[c][0] for c in syms if c in smap])
    tex = "{}".join([(smap[c][1] if c in smap else c) for c in syms])
    return score, r"{" + tex + "}"


def quiz(s):
    syms = [c.strip() for c in s.split()]
    if syms and syms[0].startswith('X'):  # annul the results
        syms = [r"\textcolor{red}{\(\times\)}" for c in syms]
    smap = {
        '+':  (1., r'\(+\)'),
        '+.': (1., r'\pd'),
        '+-': (.5, r'\(\pm\)'),
        '-+': (.5, r'\(\mp\)'),
        '-.': (0., r'\md'),
        '-':  (0., r'\(-\)'),
        '~':  (rubicon, ''),    # absent student by valid reason
        ')':  (1., r'\smiley')  # knotty question
    }
    score = sum([smap[c][0] for c in syms if c in smap])
    tex = "{}".join([(smap[c][1] if c in smap else c) for c in syms])
    return score, r"{" + tex + "}"


def colored(val, tex=None):
    """`val` must be in range [0., 1.] or larger up to 1.2"""
    if not math.isfinite(val):
        return ""
    elif 1. < val and val < 1.2:
        val = 1.
    elif val < 0. or 1. < val:
        raise UserWarning(f"val [{val}] seems to be an invalid value")

    val = round(val, 2)

    color = "red!{}".format(int(10. + 90 * (rubicon - val) / rubicon)) \
            if val < rubicon else \
            "green!{}".format(int(10. + 90 * (val - rubicon) / (1 - rubicon)))
    tex = r"\color{black}" + tex \
          if tex else \
          r"\color{gray}\makebox[1em]{\tiny" + f"{val:.2f}" + "}"

    return r"\cellcolor{" + color + "}" + tex


def colored_mark(val, tex=None):
    global rubicon
    old = rubicon
    rubicon = 0.5
    out = colored(val, tex)
    rubicon = old
    return out


def bonus(s):
    return r"\ensuremath{{{}}}".format(s)


def ctrl_mark(s):
    if s in [str(i+1) for i in range(10)]:
        return colored_mark(value(s) / 10., f"({s})")
    else:
        return s


def exam_mark(s):
    mark = None
    if s in {'1', '2'}:
        mark = "неуд"
    elif s in {'3', '4'}:
        mark = "удовл"
    elif s in {'5', '6', '7'}:
        mark = "хор"
    elif s in {'8', '9', '10'}:
        mark = "отл"
    elif s in {"н/я", "н/д"}:
        return colored_mark(0.) + s
    else:
        return s
    return colored_mark(value(s) / 10., f"{mark}.({s})")
