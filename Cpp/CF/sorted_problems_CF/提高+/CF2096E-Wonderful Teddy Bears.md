---
title: "Wonderful Teddy Bears"
layout: "post"
diff: 提高+/省选-
pid: CF2096E
tag: ['贪心']
---

# Wonderful Teddy Bears

## 题目描述

你是 $n$ 只泰迪熊的骄傲主人，它们被排成一列放在架子上。每只泰迪熊的颜色是黑色或粉色。

如果所有黑色泰迪熊都位于所有粉色泰迪熊的左侧，则称这种排列是美丽的。换句话说，不存在一对索引 $(i, j)$（$1 \leq i < j \leq n$）使得第 $i$ 只泰迪熊是粉色且第 $j$ 只泰迪熊是黑色。

你希望将这些泰迪熊重新排列成美丽的顺序。由于你够不到架子，但幸运的是，你可以向机器人发送指令来移动泰迪熊。在单条指令中，机器人可以：

- 选择一个索引 $i$（$1 \le i \le n - 2$），并将位置 $i$、$i + 1$ 和 $i + 2$ 的泰迪熊重新排列，使得所有黑色泰迪熊位于所有粉色泰迪熊的左侧。

最少需要多少条指令才能完成重新排列？

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$（$1 \le t \le 10^4$）。接下来是测试用例的描述。

每个测试用例的第一行包含一个整数 $n$（$3 \le n \le 2 \cdot 10^5$）——泰迪熊的数量。

每个测试用例的第二行包含一个长度为 $n$ 的字符串 $s$，由字符 `B` 和 `P` 组成——表示泰迪熊的颜色。对于从 $1$ 到 $n$ 的每个 $i$，如果 $s_i = \texttt{B}$，则第 $i$ 只泰迪熊是黑色；如果 $s_i = \texttt{P}$，则是粉色。

保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一个整数——完成重新排列所需的最少指令数。


## 说明/提示

对于第一个测试用例，所有泰迪熊都是粉色。因此，排列已经是美丽的，答案为 $0$。

对于第二个测试用例，所有黑色泰迪熊已经位于所有粉色泰迪熊的左侧。因此，答案为 $0$。

对于第三个测试用例，我们可以执行 $1$ 条指令，选择 $i = 1$。

执行指令后，颜色序列从 $\texttt{PPB}$ 变为 $\texttt{BPP}$，任务完成。

对于第四个测试用例，我们可以执行 $5$ 条指令如下：

- $i = 1$：$\texttt{}\color{magenta}{\texttt{PPB}}\texttt{PPBB} \rightarrow \texttt{}\color{magenta}{\texttt{BPP}}\texttt{PPBB}$
- $i = 5$：$\texttt{BPPP}\color{magenta}{\texttt{PBB}}\texttt{} \rightarrow \texttt{BPPP}\color{magenta}{\texttt{BBP}}\texttt{}$
- $i = 4$：$\texttt{BPP}\color{magenta}{\texttt{PBB}}\texttt{P} \rightarrow \texttt{BPP}\color{magenta}{\texttt{BBP}}\texttt{P}$
- $i = 3$：$\texttt{BP}\color{magenta}{\texttt{PBB}}\texttt{PP} \rightarrow \texttt{BP}\color{magenta}{\texttt{BBP}}\texttt{PP}$
- $i = 2$：$\texttt{B}\color{magenta}{\texttt{PBB}}\texttt{PPP} \rightarrow \texttt{B}\color{magenta}{\texttt{BBP}}\texttt{PPP}$

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
5
3
PPP
3
BPP
3
PPB
7
PPBPPBB
15
BPBPBBBBBPBBBBB
```

### 输出

```
0
0
1
5
14
```

