---
title: "SEQ2 - Another Sequence Problem"
layout: "post"
diff: 难度0
pid: SP1470
tag: []
---

# SEQ2 - Another Sequence Problem

## 题目描述

## 本题与 [P2042](https://www.luogu.com.cn/problem/P2042) 重题。


请编写一个程序来对给定的序列执行一些操作。操作如下：

## 输入格式

| :----------: | :----------: | :----------: |
| 修改 | `MAKE SAME i t c` | 将从第 $i$ 个数（包括其本身）开始的 $t$ 个数修改成 $c$ |
| 插入 | `INSERT i t s` | 在第 $i$ 个数后面插入一个长 $t$ 的序列 $s$ |
| 删除 | `DELETE i t` | 删除从第 $i$ 个数（包括其本身）开始的 $t$ 个数 |
| 翻转 | `REVERSE i t` | 翻转从第 $i$ 个数（包括其本身）开始的 $t$ 个数构成的序列 |
| 输出 | `GET-SUM i t` | 输出从第 $i$ 个数（包括其本身）开始的 $t$ 个数之和 |
| 求最大值 | `MAX-SUM` | 输出整个序列的**最大子段和** |


第一行 $T\ (1\leqslant T\leqslant 4)$ 为数据组数。

对每组数据：

第一行包含两个整数 $n$ 和 $m\ (m\leqslant 2\times 10^4)$，分别为初始序列长度和操作次数。

第二行为初始的长 $n$ 的序列。

后面 $m$ 行为 $m$ 个操作。

## 输出格式

对每个操作 `GET-SUM` 和 `MAX-SUM`，输出答案，每行一个数。

## 说明/提示

无论何时，序列中的每个数均在 $[-10^3,10^3]$ 范围内，序列长度不会超过 $5\times 10^5$ 也不会变成空序列。

## 样例 #1

### 输入

```
1
9 8
2 -6 3 5 1 -5 -3 6 3
GET-SUM 5 4
MAX-SUM
INSERT 8 3 -5 7 2
DELETE 12 1
MAKE-SAME 3 3 2
REVERSE 3 6
GET-SUM 5 4
MAX-SUM
```

### 输出

```
-1
10
1
10

Hints:
After the 3rd op., the sequence is 
2 -6 3 5 1 -5 -3 6 -5 7 2 3

After the 4th op., the sequence is 
2 -6 3 5 1 -5 -3 6 -5 7 2

After the 5th op., the sequence is 
2 -6 2 2 2 -5 -3 6 -5 7 2

After the 6th op., the sequence is 
2 -6 6 -3 -5 2 2 2 -5 7 2
```

