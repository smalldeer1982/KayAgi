---
title: "Multi-judge Solving"
layout: "post"
diff: 普及/提高-
pid: CF825C
tag: []
---

# Multi-judge Solving

## 题目描述

Makes solves problems on Decoforces and lots of other different online judges. Each problem is denoted by its difficulty — a positive integer number. Difficulties are measured the same across all the judges (the problem with difficulty $ d $ on Decoforces is as hard as the problem with difficulty $ d $ on any other judge).

Makes has chosen $ n $ problems to solve on Decoforces with difficulties $ a_{1},a_{2},...,a_{n} $ . He can solve these problems in arbitrary order. Though he can solve problem $ i $ with difficulty $ a_{i} $ only if he had already solved some problem with difficulty ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF825C/dcc3f539eeb6ae660df27e0ba4735db648eac084.png) (no matter on what online judge was it).

Before starting this chosen list of problems, Makes has already solved problems with maximum difficulty $ k $ .

With given conditions it's easy to see that Makes sometimes can't solve all the chosen problems, no matter what order he chooses. So he wants to solve some problems on other judges to finish solving problems from his list.

For every positive integer $ y $ there exist some problem with difficulty $ y $ on at least one judge besides Decoforces.

Makes can solve problems on any judge at any time, it isn't necessary to do problems from the chosen list one right after another.

Makes doesn't have too much free time, so he asked you to calculate the minimum number of problems he should solve on other judges in order to solve all the chosen problems from Decoforces.

## 输入格式

The first line contains two integer numbers $ n $ , $ k $ ( $ 1<=n<=10^{3} $ , $ 1<=k<=10^{9} $ ).

The second line contains $ n $ space-separated integer numbers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=10^{9} $ ).

## 输出格式

Print minimum number of problems Makes should solve on other judges in order to solve all chosen problems on Decoforces.

## 说明/提示

In the first example Makes at first solves problems 1 and 2. Then in order to solve the problem with difficulty 9, he should solve problem with difficulty no less than 5. The only available are difficulties 5 and 6 on some other judge. Solving any of these will give Makes opportunity to solve problem 3.

In the second example he can solve every problem right from the start.

## 样例 #1

### 输入

```
3 3
2 1 9

```

### 输出

```
1

```

## 样例 #2

### 输入

```
4 20
10 3 6 3

```

### 输出

```
0

```

