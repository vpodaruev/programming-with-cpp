#!/usr/bin/python3

import json
import numpy as np
import pandas as pd

import atom
import google_serve as gs


def set_rubicon(value):
    if value < 0. or 1. < value:
        raise Warning(f"rubicon must be in [0, 1], but got {value}")
    atom.rubicon = value


def numcol(table):
    num = "\\makebox[0.6em][r]{{{}}}"
    return [(r"\rowcolor{black!5}" if int(x) % 2 == 1 else "") + num.format(x)
            for x in table.index.values + 1]


def quiz_table_header(chapters):
    n = len(chapters)
    tab = "@{~~}".join(["c"]*n)
    header = " & ".join([r"\quiz{{{}}}".format(i) for i in chapters])

    return r"""\par\small\noindent
    \begin{{tabular}}{{r l {} c}}
    \toprule
     & & \multicolumn{{{}}}{{c}}{{контрольные опросы}} & \\
    \cline{{3-{}}}
    \rule{{0pt}}{{12pt}}\makebox[0.6em][r]{{№}} & Фамилия~И.О. &  {}  & ? \\
    \midrule
    """.format(tab, n, n+2, header)


def print_quiz(table):
    chapters = []
    table.columns = [item.strip() for item in table.columns]

    m = pd.DataFrame(index=table.index.values,
                     columns=["name"] + [f"quiz {i}" for i in chapters])

    m["name"] = table["name"].transform(atom.name_short)

    q = pd.DataFrame(index=table.index.values)

    for name in [item for item in table if item.startswith("quiz")]:
        chapters += [name.split(maxsplit=2)[1]]
        m[name] = table[name].transform(lambda x: atom.quiz(x)[1])
        q[name] = table[name].transform(lambda x: atom.quiz(x)[0])

    # filter quiz results to only those ideal student had done
    for item in [x for x in q if q[x][0] == 0.]:
        q[item] = 0.

    q["?"] = q.sum(axis=1)
    q["?"] /= q["?"][0]  # first element is the maximum
    m["?"] = q["?"].transform(atom.colored)

    m.insert(0, "#", numcol(m))

    tex = m.apply(lambda col: " & ".join([str(x) if x is not np.nan
                                          else "" for x in col]) + r"\\",
                  axis=1).values[1:]

    print(quiz_table_header(chapters))
    print("\n".join(tex))
    print(r"""
    \bottomrule
    \end{tabular}
    """)


def print_main(table):
    print(r"""\par\noindent
    \begin{tabular}{r l lc l ccc ccc c l ccc}
    \toprule
    & & \multicolumn{2}{c}{начальный уровень} && \multicolumn{7}{c}{контрольно-проверочные мероприятия} && \multicolumn{3}{c}{зачёт} \\
    \cline{3-4}\cline{6-12}\cline{14-16}
    \rule{0pt}{12pt}\makebox[0.6em][r]{№} & Фамилия Имя Отчество & языки & \test && \ctrl{1} & \task{1} & \ctrl{2} & \task{2}  & \qsum && ? & \(\star\) & отметка \\
    \midrule
    """)
    table.columns = [item.strip() for item in table.columns]
    table = table.transform(lambda col: [x.strip() if type(x) == str else x for x in col])

    m = pd.DataFrame(index=table.index.values,
                     columns=["name", "lang", "test", "|",
                              "ctrl 1", "mark 1", "task 1",
                              "ctrl 2", "mark 2", "task 2",
                              "qsum", "|", "?", "bonus", "mark"])

    m["name"] = table["name"].transform(atom.name)
    m["lang"] = table["lang"].transform(atom.lang)

    if "test" in table:
        m["test"] = table["test"].transform(atom.test)

    q = pd.DataFrame(index=table.index.values)

    for name in [item for item in table if item.startswith("ctrl")]:
        m[name] = table[name].transform(lambda x: atom.ctrl(x)[1])
        q[name] = table[name].transform(lambda x: atom.ctrl(x)[0])

    for name in [item for item in table if item in {"mark 1", "mark 2"}]:
        m[name] = table[name].transform(lambda x: atom.ctrl_mark(x))

    for name in [item for item in table if item.startswith("task")]:
        m[name] = table[name].transform(lambda x: atom.task(x)[1])
        q[name] = table[name].transform(lambda x: atom.task(x)[0])

    q["qsum"] = np.zeros(len(q.index))
    for name in [item for item in table if item.startswith("quiz")]:
        c = table[name].transform(lambda x: atom.quiz(x)[0])
        # filter quiz results to only those ideal student had done
        if c[0] != 0.:
            q["qsum"] += c
    m["qsum"] = q["qsum"].transform(lambda x: round(x, 1))

    for name in q:
        if not name.startswith("task"):
            q[name] /= q[name][0]
    q["?"] = q.sum(axis=1)
    q["?"] /= q["?"][0]  # first element is the maximum
    m["?"] = q["?"].transform(atom.colored)

    if "bonus" in table:
        m["bonus"] = table["bonus"].transform(lambda x: atom.bonus(x))

    if "mark" in table:
        m["mark"] = table["mark"].transform(lambda x: atom.exam_mark(x))

    m.insert(0, "#", numcol(m))

    tex = m.apply(lambda col: " & ".join([str(x) if x is not np.nan
                                          else "" for x in col]) + r"\\",
                  axis=1).values[1:]

    print("\n".join(tex))

    print(r"""
    \bottomrule
    \end{tabular}
    """)


def read_json(file):
    with file.open("r", encoding="utf-8") as f:
        buf = f.read()
    return json.loads(buf)


def read_table(gc, url):
    """Read table from Google Sheet with `url` using credentials `gc`"""
    wsht = gs.open_worksheet(gc, url)
    vals = wsht.get_all_values()
    return wsht.title, pd.DataFrame(data=vals[1:], columns=vals[0])


if __name__ == "__main__":
    pass
