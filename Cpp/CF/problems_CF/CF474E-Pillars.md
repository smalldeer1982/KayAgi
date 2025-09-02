---
title: "Pillars"
layout: "post"
diff: 提高+/省选-
pid: CF474E
tag: []
---

# Pillars

## 题目描述

Marmot found a row with $ n $ pillars. The $ i $ -th pillar has the height of $ h_{i} $ meters. Starting from one pillar $ i_{1} $ , Marmot wants to jump on the pillars $ i_{2} $ , ..., $ i_{k} $ . ( $ 1<=i_{1}<i_{2}<...<i_{k}<=n $ ). From a pillar $ i $ Marmot can jump on a pillar $ j $ only if $ i<j $ and $ |h_{i}-h_{j}|>=d $ , where $ |x| $ is the absolute value of the number $ x $ .

Now Marmot is asking you find out a jump sequence with maximal length and print it.

## 输入格式

The first line contains two integers n and d (1 ≤ n ≤ 10^5, 0 ≤ d ≤ 10^9).

The second line contains n numbers h1, h2, ..., hn (1 ≤ hi ≤ 10^15).

## 输出格式

The first line should contain one integer k, the maximal length of a jump sequence.

The second line should contain k integers i1, i2, ..., ik (1 ≤ i1 < i2 < ... < ik ≤ n), representing the pillars' indices from the maximal length jump sequence.

If there is more than one maximal length jump sequence, print any.

## 说明/提示

In the first example Marmot chooses the pillars $ 1 $ , $ 2 $ , $ 3 $ , $ 5 $ with the heights $ 1 $ , $ 3 $ , $ 6 $ , $ 4 $ . Another jump sequence of length $ 4 $ is $ 1 $ , $ 2 $ , $ 4 $ , $ 5 $ .

## 样例 #1

### 输入

```
5 2
1 3 6 7 4

```

### 输出

```
4
1 2 3 5 

```

## 样例 #2

### 输入

```
10 3
2 1 3 6 9 11 7 3 20 18

```

### 输出

```
6
1 4 6 7 8 9 

```

