---
title: "独占访问 Exclusive Access"
layout: "post"
diff: 难度0
pid: UVA1682
tag: []
---

# 独占访问 Exclusive Access

## 题目描述

多线程编程中的一个重要问题就是确保共享资源的独占访问。需要独占访问的资源称为临界区（CS），确保独占访问的算法称为互斥协议。

在本题中，假设每个程序恰好有两个线程，每个线程都是一个无限循环，重复进行以下工作：执行其他指令（与临界区无关的代码，称为 NCS），调用 enterCS，执行 CS（即临界区代码），调用 exitCS，然后继续循环。NCS 和 CS 内的代码和协议完全无关。

在本题中，用共享的单比特变量（即每个变量只能储存 $0$ 或 $1$）来实现互斥协议（即上述的 enterCS 和 exitCS）。所有变量初始化为 $0$，且读写任意一个变量只需要一条语句。两个线程可以有一个局部指令计数器 IP 指向下一条需要执行的指令。初始时，两个线程的 IP 都指向第一条指令。程序执行的每一步，计算机随机选择一个线程，执行它的 IP 所指向的指令，然后修改该线程的 IP。为了分析互斥协议，定义“合法执行过程”如下：两个线程都执行了无限多条指令；或者其中一个线程执行了无限多指令，另一个线程执行了有限多条指令以后终止，且 IP 在 NCS 中。

下表中展示了 $3$ 个互斥协议的伪代码。两个线程的 $id$ 分别为 $0$ 和 $1$，变量 $want[0]$、$want[1]$ 和 $turn$ 为共享单比特变量。以“$\texttt{+}$”开头的代码实现了 enterCS，而以“$\texttt{-}$”开头的代码实现了 exitCS，$\rm NCS()$ 和 $\rm CS()$ 表示执行 NCS 和 CS 代码，这些代码的具体内容和本题无关（假设它们不会修改共享变量）。

| 算法 $1$ | 算法 $2$ | 算法 $3$ |
| :-: | :-: | :-: |
| $\begin{aligned} & \texttt{loop forever} \\ &\quad\texttt{NCS()} \\ &\texttt{+} \ \ \texttt{loop while} \\ &\texttt{+} \ \quad \ \texttt{(turn == 1 - id)} \\ &\quad \texttt{CS()} \\ &\texttt{-} \ \  \texttt{turn <- (1 - id)} \\ &\texttt{end loop}\end{aligned}$ | $\begin{aligned} & \texttt{loop forever} \\ &\quad\texttt{NCS()} \\ &\texttt{+}\ \ \texttt{want[id] <- 1} \\ &\texttt{+} \ \ \texttt{loop while} \\ &\texttt{+} \ \quad \ \texttt{(want[1 - id] == 1)} \\ &\quad \texttt{CS()} \\ &\texttt{-} \ \ \texttt{want[id] <- 0} \\ &\texttt{end loop}\end{aligned}$ | $\begin{aligned} & \texttt{loop forever} \\ &\quad\texttt{NCS()} \\ &\texttt{+}\ \ \texttt{want[id] <- 1} \\ &\texttt{+} \ \ \texttt{turn <- (1 - id)} \\ &\texttt{+} \ \ \texttt{loop while} \\ &\texttt{+} \ \ \quad \texttt{(want[1 - id] == 1 and} \\ &\texttt{+}\ \quad\ \ \ \texttt{turn == 1 - id)} \\ &\quad \texttt{CS()} \\ &\texttt{-} \ \ \texttt{want[id] <- 0} \\ &\texttt{end loop}\end{aligned}$ |

本题的任务是判断一个给定算法是否满足以下 $3$ 个条件。

- 互斥性：在任意合法执行过程中，两个线程的 IP 不可能同时位于 CS。

- 无死锁：在任意合法执行过程中，CS 都被执行了无限多次。

- 无饥饿：在任意合法执行过程中，执行了无限多条指令的线程执行了无限多次 CS。

互斥性很容易满足：一个什么都不干的死循环就符合条件。上述的 $3$ 个算法均满足互斥性，但前两个算法不满足“无死锁”，而第三个算法（由 Gary Peterson 发明）满足所有 $3$ 个条件。

## 输入格式

输入包含多组数据。每组数据的第一行为两个整数 $m _ 1, m _ 2$（$2 \le m _ i \le 9$），即线程 $1$ 和线程 $2$ 的代码行数。接下来的 $m _ 1$ 行是线程 $1$ 的代码，再接下来的 $m _ 2$ 行是线程 $2$ 的代码。每个线程的代码都是一条指令占一行。每条指令的格式如下：首先是指令编号（顺序编号为 $1 \sim m _ i$，仅是为了可读性才放在输入中），然后是指令助记符，后边跟着若干个参数。有一种特殊的参数称为 NIP，即下一条指令的编号（保证为 $1 \sim m _ i$ 之间的整数）。一共有 $3$ 个单比特共享变量：$\tt A, B, C$。指令助记符有以下 $4$ 种：

- $\tt NCS$：非临界区代码。唯一的参数是 NIP。

- $\tt CS$：临界区代码。唯一的参数是 NIP。

- $\tt SET$：写入共享变量。包含 $3$ 个参数 $v, x, g$。$v$ 是写入的变量（$\tt A, B$ 或 $\tt C$），$x$ 是写入的值（$0$ 或 $1$），$g$ 是 NIP。

- $\tt TEST$：读取共享变量并判断它的值。包含 $3$ 个参数 $v, g _ 0, g _ 1$，其中 $v$ 是读取的变量（$\tt A, B$ 或 $\tt C$），$g _ 0$ 是 $v = 0$ 时的 NIP，$g _ 1$ 是 $v = 1$ 时的 NIP。

在每个线程的代码中，$\tt NCS$ 和 $ \tt CS$ 恰好各出现一次。代码不一定是一个典型的无限循环，但保证交替执行 $\tt CS$ 和 $\tt NCS$。输入结束标志为文件结束符（EOF）。

## 输出格式

对于每组数据，输出三个字符 $\tt Y$ 或 $\tt N$，分别表示是否满足互斥性、无死锁和无饥饿条件。

The $\KaTeX$ has been fixed by @[TemplateClass](/user/735713).

