---
title: "Multiples and Power Differences"
layout: "post"
diff: 提高+/省选-
pid: CF1485D
tag: []
---

# Multiples and Power Differences

## 题目描述

You are given a matrix $ a $ consisting of positive integers. It has $ n $ rows and $ m $ columns.

Construct a matrix $ b $ consisting of positive integers. It should have the same size as $ a $ , and the following conditions should be met:

- $ 1 \le b_{i,j} \le 10^6 $ ;
- $ b_{i,j} $ is a multiple of $ a_{i,j} $ ;
- the absolute value of the difference between numbers in any adjacent pair of cells (two cells that share the same side) in $ b $ is equal to $ k^4 $ for some integer $ k \ge 1 $ ( $ k $ is not necessarily the same for all pairs, it is own for each pair).

We can show that the answer always exists.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 2 \le n,m \le 500 $ ).

Each of the following $ n $ lines contains $ m $ integers. The $ j $ -th integer in the $ i $ -th line is $ a_{i,j} $ ( $ 1 \le a_{i,j} \le 16 $ ).

## 输出格式

The output should contain $ n $ lines each containing $ m $ integers. The $ j $ -th integer in the $ i $ -th line should be $ b_{i,j} $ .

## 说明/提示

In the first example, the matrix $ a $ can be used as the matrix $ b $ , because the absolute value of the difference between numbers in any adjacent pair of cells is $ 1 = 1^4 $ .

In the third example:

- $ 327 $ is a multiple of $ 3 $ , $ 583 $ is a multiple of $ 11 $ , $ 408 $ is a multiple of $ 12 $ , $ 664 $ is a multiple of $ 8 $ ;
- $ |408 - 327| = 3^4 $ , $ |583 - 327| = 4^4 $ , $ |664 - 408| = 4^4 $ , $ |664 - 583| = 3^4 $ .

## 样例 #1

### 输入

```
2 2
1 2
2 3
```

### 输出

```
1 2
2 3
```

## 样例 #2

### 输入

```
2 3
16 16 16
16 16 16
```

### 输出

```
16 32 48
32 48 64
```

## 样例 #3

### 输入

```
2 2
3 11
12 8
```

### 输出

```
327 583
408 664
```

