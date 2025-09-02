---
title: "SEQPAR - Partition the sequence"
layout: "post"
diff: 省选/NOI-
pid: SP685
tag: []
---

# SEQPAR - Partition the sequence

## 题目描述

给定一个包含n个元素（从1到n编号）的整数序列。

你需要找到最小值M，这样我们就可以找到k+1整数0=p(0) < p(1) < p(2) < … < p(k - 1) < p(k) = n，因此对于从0到k-1的任何i，从位置p（i）+1到位置p（i+1）的元素之和不大于M。

## 输入格式

第一行n, k两个整数

下面的n行都包括一个范围在-30000～30000的整数

## 输出格式

输出最小的数字m

## 样例 #1

### 输入

```
1
9 4
1
1
1
3
2
2
1
3
1
```

### 输出

```
5
```

