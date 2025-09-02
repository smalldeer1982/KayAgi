---
title: "And It's Non-Zero"
layout: "post"
diff: 普及/提高-
pid: CF1615B
tag: []
---

# And It's Non-Zero

## 题目描述

You are given an array consisting of all integers from $ [l, r] $ inclusive. For example, if $ l = 2 $ and $ r = 5 $ , the array would be $ [2, 3, 4, 5] $ . What's the minimum number of elements you can delete to make the [bitwise AND](https://en.wikipedia.org/wiki/Bitwise_operation#AND) of the array non-zero?

A bitwise AND is a binary operation that takes two equal-length binary representations and performs the AND operation on each pair of the corresponding bits.

## 输入格式

The first line contains one integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases. Then $ t $ cases follow.

The first line of each test case contains two integers $ l $ and $ r $ ( $ 1 \leq l \leq r \leq 2 \cdot 10^5 $ ) — the description of the array.

## 输出格式

For each test case, output a single integer — the answer to the problem.

## 说明/提示

In the first test case, the array is $ [1, 2] $ . Currently, the bitwise AND is $ 0 $ , as $ 1\ \& \ 2 = 0 $ . However, after deleting $ 1 $ (or $ 2 $ ), the array becomes $ [2] $ (or $ [1] $ ), and the bitwise AND becomes $ 2 $ (or $ 1 $ ). This can be proven to be the optimal, so the answer is $ 1 $ .

In the second test case, the array is $ [2, 3, 4, 5, 6, 7, 8] $ . Currently, the bitwise AND is $ 0 $ . However, after deleting $ 4 $ , $ 5 $ , and $ 8 $ , the array becomes $ [2, 3, 6, 7] $ , and the bitwise AND becomes $ 2 $ . This can be proven to be the optimal, so the answer is $ 3 $ . Note that there may be other ways to delete $ 3 $ elements.

## 样例 #1

### 输入

```
5
1 2
2 8
4 5
1 5
100000 200000
```

### 输出

```
1
3
0
2
31072
```

