---
title: "Cat, Fox and the Lonely Array"
layout: "post"
diff: 普及/提高-
pid: CF1973B
tag: ['二分', '位运算']
---

# Cat, Fox and the Lonely Array

## 题目描述

Today, Cat and Fox found an array $ a $ consisting of $ n $ non-negative integers.

Define the loneliness of $ a $ as the smallest positive integer $ k $ ( $ 1 \le k \le n $ ) such that for any two positive integers $ i $ and $ j $ ( $ 1 \leq i, j \leq n - k +1 $ ), the following holds: $ $$$a_i | a_{i+1} | \ldots | a_{i+k-1} = a_j | a_{j+1} | \ldots | a_{j+k-1}, $ $  where  $ x | y $  denotes the <a href="https://en.wikipedia.org/wiki/Bitwise_operation#OR">bitwise OR</a> of  $ x $  and  $ y $ . In other words, for every  $ k $  consecutive elements, their bitwise OR should be the same. Note that the loneliness of  $ a $  is well-defined, because for  $ k = n $  the condition is satisfied.</p><p>Cat and Fox want to know how lonely the array  $ a$$$ is. Help them calculate the loneliness of the found array.

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^4  $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains one integer $ n $ ( $ 1 \leq n \leq 10^5 $ ) — the length of the array $ a $ .

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \leq a_i < 2^{20} $ ) — the elements of the array.

It is guaranteed that the sum of $ n $ over all test cases doesn't exceed $ 10^5 $ .

## 输出格式

For each test case, print one integer — the loneliness of the given array.

## 说明/提示

In the first example, the loneliness of an array with a single element is always $ 1 $ , so the answer is $ 1 $ .

In the second example, the OR of each subarray of length $ k = 1 $ is $ 2 $ , so the loneliness of the whole array is $ 1 $ .

In the seventh example, it's true that $ (0 | 1 | 3) = (1 | 3 | 2) = (3 | 2 | 2) = (2 | 2 | 1) = (2 | 1 | 0) = (1 | 0 | 3) = 3 $ , so the condition is satisfied for $ k = 3 $ . We can verify that the condition is not true for any smaller $ k $ , so the answer is indeed $ 3 $ .

## 样例 #1

### 输入

```
7
1
0
3
2 2 2
3
1 0 2
5
3 0 1 4 2
5
2 0 4 0 2
7
0 0 0 0 1 2 4
8
0 1 3 2 2 1 0 3
```

### 输出

```
1
1
3
4
4
7
3
```

