# [POI 2018 R2] 诗集 Book of poetry

## 题目背景

翻译来自于 [LibreOJ](https://loj.ac/p/5071)。

## 题目描述

**题目译自 [XXV Olimpiada Informatyczna — II etap](https://sio2.mimuw.edu.pl/c/oi25-2/dashboard/) [Tomik poezji](https://szkopul.edu.pl/problemset/problem/Hhip15j-8Ro2dOb_4oB98C-G/statement/)**

著名诗人 Bajtazar 计划出版一本诗集，收录他的 $n$ 首最新诗作。每页可印刷 $s$ 行文字，诗作按顺序逐一印刷，中间无间隔。每首诗包含标题（占一行）及其后续正文，第 $i$ 首诗的正文占 $a_i$ 行。

为美观起见，标题不得印刷在页面最后一行。若前一首诗结束于页面倒数第二行，则该页最后一行需留空。Bajtazar 的诗作顺序未定，不同排列可能导致不同数量的空行。他想找出一种诗作排列，尽量减少诗集内的空行数。

## 说明/提示

**样例 1 解释**

按顺序印刷（$1,2,3$），诗作间有一空行：

$$
\begin{array}{|c|}
\hline
\texttt{1111} \\
\texttt{WWWW} \\
\texttt{WWWW} \\
\texttt{2222} \\
\texttt{WWWW} \\
\hline
\end{array}
\begin{array}{|c|}
\hline
\texttt{WWWW} \\
\texttt{WWWW} \\
\texttt{WWWW} \\
\texttt{WWWW} \\
\texttt{....} \\
\hline
\end{array}
\begin{array}{|c|}
\hline
\texttt{3333} \\
\texttt{WWWW} \\
\\
\\
\\
\hline
\end{array}
$$

最优排列（$2,3,1$）无空行：

$$
\begin{array}{|c|}
\hline
\texttt{2222} \\
\texttt{WWWW} \\
\texttt{WWWW} \\
\texttt{WWWW} \\
\texttt{WWWW} \\
\hline
\end{array}
\begin{array}{|c|}
\hline
\texttt{WWWW} \\
\texttt{3333} \\
\texttt{WWWW} \\
\texttt{1111} \\
\texttt{WWWW} \\
\hline
\end{array}
\begin{array}{|c|}
\hline
\texttt{WWWW} \\
\\
\\
\\
\\
\hline
\end{array}
$$

**附加样例**

1. $n=5, s=2$。
2. $n=1000, s=100, a_i=98$，每种排列需 $999$ 空行。
3. $n=1000, s=1003, a_i=i$，诗作 $i$ 和 $n+1-i$ 恰填满一页，无空行。

详细子任务附加限制及分值如下表所示。

| 子任务 | 附加限制 | 分值 |
| :---: | :--: | :---: |
| $1$    | $n \leq 10$              | $10$ |
| $2$    | $n \leq 500000$，$a_i$ 两两不同，$a_i \leq s$ | $20$ |
| $3$    | $n \leq 1000$            | $25$ |
| $4$    | $n \leq 500000$          | $45$ |

## 样例 #1

### 输入

```
3 5
2 5 1```

### 输出

```
0
2 3 1```

