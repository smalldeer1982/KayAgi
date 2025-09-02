---
title: "Sum"
layout: "post"
diff: 省选/NOI-
pid: CF1442D
tag: []
---

# Sum

## 题目描述

You are given $ n $ non-decreasing arrays of non-negative numbers.

Vasya repeats the following operation $ k $ times:

- Selects a non-empty array.
- Puts the first element of the selected array in his pocket.
- Removes the first element from the selected array.

Vasya wants to maximize the sum of the elements in his pocket.

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 1 \le n, k \le 3\,000 $ ): the number of arrays and operations.

Each of the next $ n $ lines contain an array. The first integer in each line is $ t_i $ ( $ 1 \le t_i \le 10^6 $ ): the size of the $ i $ -th array. The following $ t_i $ integers $ a_{i, j} $ ( $ 0 \le a_{i, 1} \le \ldots \le a_{i, t_i} \le 10^8 $ ) are the elements of the $ i $ -th array.

It is guaranteed that $ k \le \sum\limits_{i=1}^n t_i \le 10^6 $ .

## 输出格式

Print one integer: the maximum possible sum of all elements in Vasya's pocket after $ k $ operations.

## 样例 #1

### 输入

```
3 3
2 5 10
3 1 2 3
2 1 20
```

### 输出

```
26
```

