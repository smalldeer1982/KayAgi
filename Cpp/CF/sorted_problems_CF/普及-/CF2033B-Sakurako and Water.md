---
title: "Sakurako and Water"
layout: "post"
diff: 普及-
pid: CF2033B
tag: ['贪心']
---

# Sakurako and Water

## 题目描述

During her journey with Kosuke, Sakurako and Kosuke found a valley that can be represented as a matrix of size $ n \times n $ , where at the intersection of the $ i $ -th row and the $ j $ -th column is a mountain with a height of $ a_{i,j} $ . If $ a_{i,j} < 0 $ , then there is a lake there.

Kosuke is very afraid of water, so Sakurako needs to help him:

- With her magic, she can select a square area of mountains and increase the height of each mountain on the main diagonal of that area by exactly one.

More formally, she can choose a submatrix with the upper left corner located at $ (i, j) $ and the lower right corner at $ (p, q) $ , such that $ p-i=q-j $ . She can then add one to each element at the intersection of the $ (i + k) $ -th row and the $ (j + k) $ -th column, for all $ k $ such that $ 0 \le k \le p-i $ .

Determine the minimum number of times Sakurako must use her magic so that there are no lakes.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 200 $ ) — the number of test cases.

Each test case is described as follows:

- The first line of each test case consists of a single number $ n $ ( $ 1 \le n \le 500 $ ).
- Each of the following $ n $ lines consists of $ n $ integers separated by spaces, which correspond to the heights of the mountains in the valley $ a $ ( $ -10^5 \le a_{i,j} \le 10^5 $ ).

It is guaranteed that the sum of $ n $ across all test cases does not exceed $ 1000 $ .

## 输出格式

For each test case, output the minimum number of times Sakurako will have to use her magic so that all lakes disappear.

## 样例 #1

### 输入

```
4
1
1
2
-1 2
3 0
3
1 2 3
-2 1 -1
0 0 -1
5
1 1 -1 -1 3
-3 1 4 4 -4
-1 -1 3 0 -5
4 5 3 -3 -1
3 1 -3 -1 5
```

### 输出

```
0
1
4
19
```

