---
title: "Beautiful Array"
layout: "post"
diff: 普及+/提高
pid: CF1986E
tag: ['数论']
---

# Beautiful Array

## 题目描述

You are given an array of integers $ a_1, a_2, \ldots, a_n $ and an integer $ k $ . You need to make it beautiful with the least amount of operations.

Before applying operations, you can shuffle the array elements as you like. For one operation, you can do the following:

- Choose an index $ 1 \leq i \leq n $ ,
- Make $ a_i = a_i + k $ .

The array $ b_1, b_2, \ldots, b_n $ is beautiful if $ b_i = b_{n - i + 1} $ for all $ 1 \leq i \leq n $ .

Find the minimum number of operations needed to make the array beautiful, or report that it is impossible.

## 输入格式

Each test consists of several sets of input data. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of sets of input data. Then follows their description.

The first line of each set of input data contains two integers $ n $ and $ k $ ( $ 1 \leq n \leq 10^5 $ , $ 1 \leq k \leq 10^9 $ ) — the size of the array $ a $ and the number $ k $ from the problem statement.

The second line of each set of input data contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \leq a_i \leq 10^9 $ ) — the elements of the array $ a $ .

It is guaranteed that the sum of $ n $ over all sets of input data does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each set of input data, output the minimum number of operations needed to make the array beautiful, or $ -1 $ if it is impossible.

## 说明/提示

In the first set of input data, the array is already beautiful.

In the second set of input data, you can shuffle the array before the operations and perform the operation with index $ i = 1 $ for $ 83966524 $ times.

In the third set of input data, you can shuffle the array $ a $ and make it equal to $ [2, 3, 1] $ . Then apply the operation with index $ i = 3 $ to get the array $ [2, 3, 2] $ , which is beautiful.

In the eighth set of input data, there is no set of operations and no way to shuffle the elements to make the array beautiful.

In the ninth set of input data, the array is already beautiful.

## 样例 #1

### 输入

```
11
1 1000000000
1
2 1
624323799 708290323
3 1
3 2 1
4 1
7 1 5 3
5 1
11 2 15 7 10
7 1
1 8 2 16 8 16 31
13 1
2 1 1 3 3 11 12 22 45 777 777 1500 74
10 2
1 2 1 2 1 2 1 2 1 2
11 2
1 2 1 2 1 2 1 2 1 2 1
13 3
2 3 9 14 17 10 22 20 18 30 1 4 28
5 1
2 3 5 3 5
```

### 输出

```
0
83966524
1
4
6
1
48
-1
0
14
0
```

