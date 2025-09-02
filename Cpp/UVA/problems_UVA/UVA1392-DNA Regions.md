---
title: "DNA Regions"
layout: "post"
diff: 省选/NOI-
pid: UVA1392
tag: ['单调队列', '枚举', '排序']
---

# DNA Regions

## 题目描述

## 题面
给定两个长度为 $n$ 的字符串 $A$ 和 $B$，满足 $A$ 和 $B$ 都只由大写字母 A、C、G、T 组成。

求一个长度最长的闭区间 $[L,R]$，满足对于 $i \in [L,R]$，有不超过 $p \%$ 的 $i$ 满足 $A_i \neq B_i$。

## 输入格式

包含多组数据。

对于每组数据，第一行为两个整数 $n$ 和 $q$。
接下来两行分别是 $A$ 和 $B$。

结束的标志是 $n=0$。

## 输出格式

对于每组数据，若有解，输出满足条件的区间长度的最大值，若无解，输出`No solution.`。

## 输入输出样例
### 输入
```
14 25
ACCGGTAACGTGAA
ACTGGATACGTAAA
14 24
ACCGGTAACGTGAA
ACTGGATACGTAAA
8 1
AAAAAAAA
CCCCCCCC
8 33
AAACAAAA
CCCCCCCC
0 0

```
### 输出
```
8
7
No solution.
1
```

## 说明/提示

$1 \le n \le 1.5 \times 10^5$，$1 \le p \le 99$。

