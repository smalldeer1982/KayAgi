---
title: "LCM Sum (hard version)"
layout: "post"
diff: 省选/NOI-
pid: CF1712E2
tag: ['线段树', '树状数组', '数论']
---

# LCM Sum (hard version)

## 题目描述

We are sum for we are many

Some Number



This version of the problem differs from the previous one only in the constraint on $ t $ . You can make hacks only if both versions of the problem are solved.

You are given two positive integers $ l $ and $ r $ .

Count the number of distinct triplets of integers $ (i, j, k) $ such that $ l \le i < j < k \le r $ and $ \operatorname{lcm}(i,j,k) \ge i + j + k $ .

Here $ \operatorname{lcm}(i, j, k) $ denotes the [least common multiple (LCM)](https://en.wikipedia.org/wiki/Least_common_multiple) of integers $ i $ , $ j $ , and $ k $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ \bf{1 \le t \le 10^5} $ ). Description of the test cases follows.

The only line for each test case contains two integers $ l $ and $ r $ ( $ 1 \le l \le r \le 2 \cdot 10^5 $ , $ l + 2 \le r $ ).

## 输出格式

For each test case print one integer — the number of suitable triplets.

## 说明/提示

In the first test case, there are $ 3 $ suitable triplets:

- $ (1,2,3) $ ,
- $ (1,3,4) $ ,
- $ (2,3,4) $ .

In the second test case, there is $ 1 $ suitable triplet:

- $ (3,4,5) $ .

## 样例 #1

### 输入

```
5
1 4
3 5
8 86
68 86
6 86868
```

### 输出

```
3
1
78975
969
109229059713337
```

