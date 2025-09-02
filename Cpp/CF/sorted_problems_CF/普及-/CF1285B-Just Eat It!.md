---
title: "Just Eat It!"
layout: "post"
diff: 普及-
pid: CF1285B
tag: []
---

# Just Eat It!

## 题目描述

### 题意简述

给定长度为 $n$ 的数列 $a=[a_1,a_2,...,a_n]$。

Yasser 会选择所有的 $n$ 个数，并算出它们的和 $\sum a_i$。

Adel 会选择两个正整数 $l,r(1\leq l \leq r \leq n)$，并算出 $\sum_{i=l}^{r} a_i$。Adel 不能选择 $l=1,r=n$。

如果 Yasser 算出的和在任意情况下（即 Adel 选取任意的 $l,r$ 都是如此）**严格大于** Adel 算出的，那么 Yasser 会开心。否则 Yasser 不会开心。

请你判断 Yasser 是否开心。

## 输入格式

**本题有多组数据**。

第一行一个正整数 $t(1\leq t \leq 10^4)$，表示数据的组数。

对于每组数据，第一行一个正整数 $n(2\leq n \leq 10^5)$。

接下来一行 $a_1,a_2,...,a_n(-10^{9} \leq a_i \leq 10^9)$。

保证 $\sum n$ 不会超过 $10^5$。

## 输出格式

对于每组数据，如果 Yasser 会开心，输出 `YES`，否则输出 `NO`。

翻译贡献者 U108949

## 样例 #1

### 输入

```
3
4
1 2 3 4
3
7 4 -1
3
5 -5 5
```

### 输出

```
YES
NO
NO
```

