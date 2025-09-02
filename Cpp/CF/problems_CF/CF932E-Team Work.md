---
title: "Team Work"
layout: "post"
diff: 省选/NOI-
pid: CF932E
tag: []
---

# Team Work

## 题目描述

You have a team of $ N $ people. For a particular task, you can pick any non-empty subset of people. The cost of having $ x $ people for the task is $ x^{k} $ .

Output the sum of costs over all non-empty subsets of people.

## 输入格式

Only line of input contains two integers $ N $ $ (1<=N<=10^{9}) $ representing total number of people and $ k $ $ (1<=k<=5000) $ .

## 输出格式

Output the sum of costs for all non empty subsets modulo $ 10^{9}+7 $ .

## 说明/提示

In the first example, there is only one non-empty subset $ {1} $ with cost $ 1^{1}=1 $ .

In the second example, there are seven non-empty subsets.

\- $ {1} $ with cost $ 1^{2}=1 $

\- $ {2} $ with cost $ 1^{2}=1 $

\- $ {1,2} $ with cost $ 2^{2}=4 $

\- $ {3} $ with cost $ 1^{2}=1 $

\- $ {1,3} $ with cost $ 2^{2}=4 $

\- $ {2,3} $ with cost $ 2^{2}=4 $

\- $ {1,2,3} $ with cost $ 3^{2}=9 $

The total cost is $ 1+1+4+1+4+4+9=24 $ .

## 样例 #1

### 输入

```
1 1

```

### 输出

```
1

```

## 样例 #2

### 输入

```
3 2

```

### 输出

```
24

```

