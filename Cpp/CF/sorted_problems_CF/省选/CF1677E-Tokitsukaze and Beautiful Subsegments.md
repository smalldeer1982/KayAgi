---
title: "Tokitsukaze and Beautiful Subsegments"
layout: "post"
diff: 省选/NOI-
pid: CF1677E
tag: []
---

# Tokitsukaze and Beautiful Subsegments

## 题目描述

Tokitsukaze has a permutation $ p $ of length $ n $ .

Let's call a segment $ [l,r] $ beautiful if there exist $ i $ and $ j $ satisfying $ p_i \cdot p_j = \max\{p_l, p_{l+1}, \ldots, p_r \} $ , where $ l \leq i < j \leq r $ .

Now Tokitsukaze has $ q $ queries, in the $ i $ -th query she wants to know how many beautiful subsegments $ [x,y] $ there are in the segment $ [l_i,r_i] $ (i. e. $ l_i \leq x \leq y \leq r_i $ ).

## 输入格式

The first line contains two integers $ n $ and $ q $ ( $ 1\leq n \leq 2 \cdot 10^5 $ ; $ 1 \leq q \leq 10^6 $ ) — the length of permutation $ p $ and the number of queries.

The second line contains $ n $ distinct integers $ p_1, p_2, \ldots, p_n $ ( $ 1 \leq p_i \leq n $ ) — the permutation $ p $ .

Each of the next $ q $ lines contains two integers $ l_i $ and $ r_i $ ( $ 1 \leq l_i \leq r_i \leq n $ ) — the segment $ [l_i,r_i] $ of this query.

## 输出格式

For each query, print one integer — the numbers of beautiful subsegments in the segment $ [l_i,r_i] $ .

## 说明/提示

In the first example, for the first query, there are $ 2 $ beautiful subsegments — $ [1,2] $ and $ [1,3] $ .

## 样例 #1

### 输入

```
8 3
1 3 5 2 4 7 6 8
1 3
1 1
1 8
```

### 输出

```
2
0
10
```

## 样例 #2

### 输入

```
10 10
6 1 3 2 5 8 4 10 7 9
1 8
1 10
1 2
1 4
2 4
5 8
4 10
4 7
8 10
5 9
```

### 输出

```
17
25
1
5
2
0
4
1
0
0
```

