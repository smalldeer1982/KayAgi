---
title: "Lookup Tables"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1423I
tag: []
---

# Lookup Tables

## 题目描述

John 有 $Q$ 个闭区间 $[l_i, r_i]$，区间中是连续的 $2K$ 位数字，每个区间对应一个 16 位的数值 $v_i$（$0 \leq i < Q$）。

John 希望实现一个函数 $F$，这个函数将 $2K$ 位的数字映射为 16 位数字，使得每个区间内的所有输入都能映射到该区间的值。具体来说，对于每一个 $0 \leq i < Q$ 和每个 $x \in [l_i, r_i]$，都有 $F(x) = v_i$。对于不在任何区间中的输入，$F(x)$ 的输出无需关心。

为提高函数 $F$ 的实现效率，John 决定使用查找表。但考虑到一个完整的 $2K$ 位查找表太大，无法放入内存，他计划使用两个 $K$ 位的查找表，分别是 LSBTable 和 MSBTable。具体实现方式为：
$$ F(x) = \textrm{LSBTable}[\textrm{lowKBits}(x)] \; \& \; \textrm{MSBTable}[\textrm{highKBits}(x)] $$
即，返回在 LSBTable 中查找 $x$ 的低 $K$ 位和在 MSBTable 中查找 $x$ 的高 $K$ 位的结果，并进行位与运算。

John 需要你的帮助。已知 $K$ 和 $Q$ 以及 $Q$ 个区间 $[l_i, r_i]$ 和对应的值 $v_i$，你需要找到一对查找表 LSBTable 和 MSBTable 来实现函数 $F$，或者告知无法实现。

## 输入格式

第一行包含两个整数 $K$ 和 $Q$，分别表示位数和区间个数（$1 \leq K \leq 16$，$1 \leq Q \leq 2 \cdot 10^5$）。

接下来的 $Q$ 行，每行包含三个整数 $l_i$、$r_i$ 和 $v_i$，表示区间范围和对应的值（$0 \leq l_i \leq r_i < 2^{2K}$，$0 \leq v_i < 2^{16}$）。

## 输出格式

如果存在符合要求的查找表，输出第一行应为“possible”（不包含引号），否则输出“impossible”（不包含引号）。

如果有解，接下来的 $2 \cdot 2^K$ 行中输出计算出的 LSBTable 和 MSBTable 的所有值。如果解不唯一，可以输出任意满足条件的解。

第 $1 + i$ 行输出 $\textrm{LSBTable}[i]$（$0 \leq i < 2^K$，$0 \leq \textrm{LSBTable}[i] < 2^{16}$）。

第 $1 + 2^K + i$ 行输出 $\textrm{MSBTable}[i]$（$0 \leq i < 2^K$，$0 \leq \textrm{MSBTable}[i] < 2^{16}$）。

## 说明/提示

闭区间 $[a, b]$ 包含 $a$ 和 $b$。

在第一个样例中，LSBTable 为 $[1, 3]$，MSBTable 为 $[1, 3]$ 时满足条件：$F[0] = 1 \& 1 = 1$，$F[1] = 3 \& 1 = 1$，$F[2] = 1 \& 3 = 1$，$F[3] = 3 \& 3 = 3$。

在第二个样例中，LSBTable 为 $[3, 3, 2, 2]$，MSBTable 为 $[0, 3, 0, 1]$ 时满足所有条件。

在第三个样例中，无法找到两个查找表满足要求。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
1 2
0 2 1
3 3 3
```

### 输出

```
possible
1
3
1
3
```

## 样例 #2

### 输入

```
2 4
4 5 3
6 7 2
0 3 0
12 13 1
```

### 输出

```
possible
3
3
2
2
0
3
0
1
```

## 样例 #3

### 输入

```
2 3
4 4 3
5 6 2
12 14 1
```

### 输出

```
impossible
```

