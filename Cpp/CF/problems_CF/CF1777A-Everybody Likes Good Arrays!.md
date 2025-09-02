---
title: "Everybody Likes Good Arrays!"
layout: "post"
diff: 入门
pid: CF1777A
tag: []
---

# Everybody Likes Good Arrays!

## 题目描述

An array $ a $ is good if for all pairs of adjacent elements, $ a_i $ and $ a_{i+1} $ ( $ 1\le i \lt n $ ) are of different parity. Note that an array of size $ 1 $ is trivially good.

You are given an array of size $ n $ .

In one operation you can select any pair of adjacent elements in which both elements are of the same parity, delete them, and insert their product in the same position.

Find the minimum number of operations to form a good array.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 500 $ ). The description of the test cases follows.

The first line of each test case contains an integer $ n $ ( $ 1 \le n \le 100 $ ).

The second line of each test case contains $ n $ integers $ a_1,a_2,\ldots,a_n $ ( $ 1 \le a_i \le 10^{9} $ ).

## 输出格式

For each test case print an integer, the minimum number of operations required to form a good array.

## 说明/提示

Consider the first test case. Select the $ 2 $ -nd and the $ 3 $ -rd integers and apply the operation on them. The array changes from $ [1, \color{red}{7}, \color{red}{11}, 2, 13] $ to $ [1, \color{red}{77}, 2, 13] $ . Next, select the $ 1 $ -st and the $ 2 $ -nd integers, array changes from $ [\color{red}{1}, \color{red}{77}, 2, 13] $ to $ [\color{red}{77}, 2, 13] $ . Thus we require $ 2 $ operations. It can be proved that this is the minimum number of operations.

In the second test case, the given array is already good. So we require $ 0 $ operations.

## 样例 #1

### 输入

```
3
5
1 7 11 2 13
4
1 2 3 4
6
1 1 1 2 2 3
```

### 输出

```
2
0
3
```

