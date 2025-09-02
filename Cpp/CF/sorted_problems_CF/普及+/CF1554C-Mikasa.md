---
title: "Mikasa"
layout: "post"
diff: 普及+/提高
pid: CF1554C
tag: []
---

# Mikasa

## 题目描述

给出两个整数 $n$ 和 $m$。请你求出序列 $n \oplus 0,n \oplus 1,\dots,n \oplus m$ 的 $\operatorname{MEX}$。此处 $\oplus$ 是位运算[异或](https://baike.baidu.com/item/%E5%BC%82%E6%88%96)。

一个序列的 $\operatorname{MEX}$ 定义为序列中没有出现的最小的非负整数。例如：$\operatorname{MEX}(0,1,2,4)=3$ 和 $\operatorname{MEX}(1,2021)=0$。

## 输入格式

第一行包含一个整数 $t$ 表示数据组数。

接下来的 $t$ 行，每行包含两个整数 $n$ 和 $m$作为一组数据，意义如上。

## 输出格式

对于每组数据，换行输出一个整数作为答案。

## 说明/提示

$1 \leq t \leq 3\times10^4$

$0 \leq n,m \leq 1\times10^9$

在样例的第一组数据中，序列为 $3 \oplus 0, 3 \oplus 1, 3 \oplus 2, 3 \oplus 3, 3 \oplus 4, 3 \oplus 5$ 即 $3, 2, 1, 0, 7, 6$。其中没有出现的最小的非负整数是 $4$，则序列的 $\operatorname{MEX}$ 为 $4$。

在样例的第二组数据中，序列为 $4 \oplus 0,4 \oplus 1,4 \oplus 2,4 \oplus 3,4 \oplus 4,4 \oplus 5,4 \oplus 6$ 即 $4, 5, 6, 7, 0, 1, 2$。其中没有出现的最小的非负整数是 $3$，则序列的 $\operatorname{MEX}$ 为 $3$。

在样例的第三组数据中，序列为 $3 \oplus 0,3 \oplus 1,3 \oplus 2 $ 即 $3, 2, 1$。其中没有出现的最小的非负整数是 $0$，则序列的 $\operatorname{MEX}$ 为 $0$。

## 样例 #1

### 输入

```
5
3 5
4 6
3 2
69 696
123456 654321
```

### 输出

```
4
3
0
640
530866
```

