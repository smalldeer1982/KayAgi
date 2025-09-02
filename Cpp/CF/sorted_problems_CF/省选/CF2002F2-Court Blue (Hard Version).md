---
title: "Court Blue (Hard Version)"
layout: "post"
diff: 省选/NOI-
pid: CF2002F2
tag: ['数论']
---

# Court Blue (Hard Version)

## 题目描述

This is the hard version of the problem. In this version, it is not guaranteed that $ n=m $ , and the time limit is higher. You can make hacks only if both versions of the problem are solved.

In the court of the Blue King, Lelle and Flamm are having a performance match. The match consists of several rounds. In each round, either Lelle or Flamm wins.

Let $ W_L $ and $ W_F $ denote the number of wins of Lelle and Flamm, respectively. The Blue King considers a match to be successful if and only if:

- after every round, $ \gcd(W_L,W_F)\le 1 $ ;
- at the end of the match, $ W_L\le n, W_F\le m $ .

Note that $ \gcd(0,x)=\gcd(x,0)=x $ for every non-negative integer $ x $ .

Lelle and Flamm can decide to stop the match whenever they want, and the final score of the performance is $ l \cdot W_L + f \cdot W_F $ .

Please help Lelle and Flamm coordinate their wins and losses such that the performance is successful, and the total score of the performance is maximized.

## 输入格式

The first line contains an integer $ t $ ( $ 1\leq t \leq 10^3 $ ) — the number of test cases.

The only line of each test case contains four integers $ n $ , $ m $ , $ l $ , $ f $ ( $ 2\leq n\leq m \leq 2\cdot 10^7 $ , $ 1\leq l,f \leq 10^9 $ ): $ n $ , $ m $ give the upper bound on the number of Lelle and Flamm's wins, $ l $ and $ f $ determine the final score of the performance.

Unusual additional constraint: it is guaranteed that, for each test, there are no pairs of test cases with the same pair of $ n $ , $ m $ .

## 输出格式

For each test case, output a single integer — the maximum total score of a successful performance.

## 说明/提示

In the first test case, a possible performance is as follows:

- Flamm wins, $ \gcd(0,1)=1 $ .
- Lelle wins, $ \gcd(1,1)=1 $ .
- Flamm wins, $ \gcd(1,2)=1 $ .
- Flamm wins, $ \gcd(1,3)=1 $ .
- Flamm wins, $ \gcd(1,4)=1 $ .
- Lelle and Flamm agree to stop the match.

The final score is $ 1\cdot2+4\cdot5=22 $ .

## 样例 #1

### 输入

```
8
3 4 2 5
4 4 1 4
6 6 2 2
7 9 2 3
8 9 9 1
2 7 1 4
5 9 1 4
5 6 6 7
```

### 输出

```
22
17
18
37
77
30
41
59
```

## 样例 #2

### 输入

```
2
3082823 20000000 1341 331
20000000 20000000 3 5
```

### 输出

```
10754065643
159999991
```

## 样例 #3

### 输入

```
1
139 1293 193 412
```

### 输出

```
559543
```

