---
title: "Mateusz and an Infinite Sequence"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1097H
tag: []
---

# Mateusz and an Infinite Sequence

## 题目描述

给出整数 $m,d$ 和一个序列 $\textrm{gen}$，保证 $\textrm{gen}_1 = 0$。

对两个整数序列 $S$ 和 $T$ 定义 $S+T$ 表示将序列 $T$ 拼接在序列 $S$ 后得到的序列；

对于一个整数序列 $S$ 和一个整数 $x$ 定义 $S+x$ 表示对序列 $S$ 中的所有数 $p$ 进行操作 $p \leftarrow (p+x) \bmod m$ 得到的序列；

定义序列 $M_i$：

- 如果 $i=0$，则 $M_i = \{0\}$
- 否则 $M_i = (M_{i-1}+\textrm{gen}_1)+(M_{i-1} + \textrm{gen}_2) + \ldots + (M_{i-1} + \textrm{gen}_d)$。

因为 $\textrm{gen}_1=0$，所以对于 $i>0$，$M_{i-1}$ 是 $M_i$ 的前缀，故 $M_\infty$ 是良定义的。

接下来给出一个长度为 $n$ 的序列 $B$ 和两个整数 $l,r$，定义序列 $A$ 表示 $M_\infty$ 中第 $l$ 到第 $r$ 个元素依次形成的序列，注意序列下标从 $1$ 开始。

定义序列 $P$ 严格大于序列 $Q$ 当且仅当 $|P| = |Q|$ 且 $\forall i \in[1,|Q|],P_i \geq Q_i$。

对于序列 $A$ 的 $|A|-n+1$ 个长度为 $n$ 的连续子串，你需要给出其中 $B$ 严格大于的子串有多少个。

## 输入格式

第一行两个整数 $d,m(2 \leq d \leq 20,2 \leq m \leq 60)$，第二行 $d$ 个整数描述序列 $\textrm{gen}$，$0 < \textrm{gen}_i \leq 60,\textrm{gen}_1 = 0$。

接下来一行一个整数 $n(1 \leq n \leq 3 \times 10^4)$，接下来 $n$ 个整数描述序列 $B,0 \leq B_i < m$。

最后一行两个整数 $l,r(1 \leq l \leq r \leq 10^{18},r-l+1 \geq n)$ 描述序列 $A$。

## 输出格式

一行一个整数表示答案。

## 样例 #1

### 输入

```
2 2
0 1
4
0 1 1 0
2 21

```

### 输出

```
6

```

## 样例 #2

### 输入

```
3 4
0 1 2
2
0 2
6 11

```

### 输出

```
1

```

