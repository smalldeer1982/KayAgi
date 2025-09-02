---
title: "ALTSEQ - Alternating Sequences"
layout: "post"
diff: 难度0
pid: SP27307
tag: []
---

# ALTSEQ - Alternating Sequences

## 题目描述

给定一个由 $N$ 个整数$a_1$、$a_2$、$a_3$ … $a_n$组成的数组 $a$，求该数组的最长交替子序列。

交替序列 $b_1$、$b_2$ … $b_k$ ($k \ge 1$)是具有以下 $2$ 个特性的序列：   
1.$\left | b_1 \right | < \left | b_2 \right | < \left | b_3 \right | < ..... < \left | b_k \right |$  

2.符号在相邻元素之间交替，即，若 $b_1 >  0$，则 $b_2 < 0$，依此类推。

保证数组 $a$ 不包含 $0$ 。

## 输入格式

第一行包含一个整数 $N$，表示数组的大小。下一行包含 $N$ 个整数，表示数组 $a$。

## 输出格式

输出最长交替子序列的长度。

## 样例 #1

### 输入

```
8
1 2 -2 -3 5 -7 -8 10
```

### 输出

```
5
```

