---
title: "Swapping Problem"
layout: "post"
diff: 省选/NOI-
pid: CF1513F
tag: []
---

# Swapping Problem

## 题目描述

You are given 2 arrays $ a $ and $ b $ , both of size $ n $ . You can swap two elements in $ b $ at most once (or leave it as it is), and you are required to minimize the value $ $$$\sum_{i}|a_{i}-b_{i}|. $ $$$

Find the minimum possible value of this sum.

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ).

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le {10^9} $ ).

The third line contains $ n $ integers $ b_1, b_2, \ldots, b_n $ ( $ 1 \le b_i \le {10^9} $ ).

## 输出格式

Output the minimum value of $ \sum_{i}|a_{i}-b_{i}| $ .

## 说明/提示

In the first example, we can swap the first and fifth element in array $ b $ , so that it becomes $ [ 5, 2, 3, 4, 1 ] $ .

Therefore, the minimum possible value of this sum would be $ |5-5| + |4-2| + |3-3| + |2-4| + |1-1| = 4 $ .

In the second example, we can swap the first and second elements. So, our answer would be $ 2 $ .

## 样例 #1

### 输入

```
5
5 4 3 2 1
1 2 3 4 5
```

### 输出

```
4
```

## 样例 #2

### 输入

```
2
1 3
4 2
```

### 输出

```
2
```

