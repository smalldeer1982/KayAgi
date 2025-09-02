---
title: "Court Blue (Easy Version)"
layout: "post"
diff: 提高+/省选-
pid: CF2002F1
tag: ['数论']
---

# Court Blue (Easy Version)

## 题目描述

This is the easy version of the problem. In this version, $ n=m $ and the time limit is lower. You can make hacks only if both versions of the problem are solved.

In the court of the Blue King, Lelle and Flamm are having a performance match. The match consists of several rounds. In each round, either Lelle or Flamm wins.

Let $ W_L $ and $ W_F $ denote the number of wins of Lelle and Flamm, respectively. The Blue King considers a match to be successful if and only if:

- after every round, $ \gcd(W_L,W_F)\le 1 $ ;
- at the end of the match, $ W_L\le n, W_F\le m $ .

Note that $ \gcd(0,x)=\gcd(x,0)=x $ for every non-negative integer $ x $ .

Lelle and Flamm can decide to stop the match whenever they want, and the final score of the performance is $ l \cdot W_L + f \cdot W_F $ .

Please help Lelle and Flamm coordinate their wins and losses such that the performance is successful, and the total score of the performance is maximized.

## 输入格式

The first line contains an integer $ t $ ( $ 1\leq t \leq 10^3 $ ) — the number of test cases.

The only line of each test case contains four integers $ n $ , $ m $ , $ l $ , $ f $ ( $ 2\leq n\leq m \leq 2\cdot 10^7 $ , $ 1\leq l,f \leq 10^9 $ , $ \bf{n=m} $ ): $ n $ , $ m $ gives the upper bound on the number of Lelle and Flamm's wins, $ l $ and $ f $ determine the final score of the performance.

Unusual additional constraint: it is guaranteed that, for each test, there are no pairs of test cases with the same pair of $ n $ , $ m $ .

## 输出格式

For each test case, output a single integer — the maximum total score of a successful performance.

## 说明/提示

In the first test case, a possible performance is as follows:

- Flamm wins, $ \gcd(0,1)=1 $ .
- Lelle wins, $ \gcd(1,1)=1 $ .
- Flamm wins, $ \gcd(1,2)=1 $ .
- Flamm wins, $ \gcd(1,3)=1 $ .
- Lelle wins, $ \gcd(2,3)=1 $ .
- Lelle and Flamm agree to stop the match.

The final score is $ 2\cdot2+3\cdot5=19 $ .

In the third test case, a possible performance is as follows:

- Flamm wins, $ \gcd(0,1)=1 $ .
- Lelle wins, $ \gcd(1,1)=1 $ .
- Lelle wins, $ \gcd(2,1)=1 $ .
- Lelle wins, $ \gcd(3,1)=1 $ .
- Lelle wins, $ \gcd(4,1)=1 $ .
- Lelle wins, $ \gcd(5,1)=1 $ .
- Flamm wins, $ \gcd(5,2)=1 $ .
- Flamm wins, $ \gcd(5,3)=1 $ .
- Flamm wins, $ \gcd(5,4)=1 $ .
- Lelle and Flamm agree to stop the match.

The final score is $ 5\cdot2+4\cdot2=18 $ . Note that Lelle and Flamm can stop the match even if neither of them has $ n $ wins.

## 样例 #1

### 输入

```
8
3 3 2 5
4 4 1 4
6 6 2 2
7 7 2 3
9 9 9 1
2 2 1 4
5 5 1 4
8 8 6 7
```

### 输出

```
19
17
18
33
86
9
24
86
```

## 样例 #2

### 输入

```
1
20000000 20000000 1341 331
```

### 输出

```
33439999007
```

## 样例 #3

### 输入

```
2
1984 1984 19 84
9982 9982 44 35
```

### 输出

```
204143
788403
```

