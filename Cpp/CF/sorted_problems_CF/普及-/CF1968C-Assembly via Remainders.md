---
title: "Assembly via Remainders"
layout: "post"
diff: 普及-
pid: CF1968C
tag: ['数学']
---

# Assembly via Remainders

## 题目描述

You are given an array $ x_2,x_3,\dots,x_n $ . Your task is to find any array $ a_1,\dots,a_n $ , where:

- $ 1\le a_i\le 10^9 $ for all $ 1\le i\le n $ .
- $ x_i=a_i \bmod a_{i-1} $ for all $ 2\le i\le n $ .

Here $ c\bmod d $ denotes the remainder of the division of the integer $ c $ by the integer $ d $ . For example $ 5 \bmod 2 = 1 $ , $ 72 \bmod 3 = 0 $ , $ 143 \bmod 14 = 3 $ .

Note that if there is more than one $ a $ which satisfies the statement, you are allowed to find any.

## 输入格式

The first line contains a single integer $ t $ $ (1\le t\le 10^4) $ — the number of test cases.

The first line of each test case contains a single integer $ n $ $ (2\le n\le 500) $ — the number of elements in $ a $ .

The second line of each test case contains $ n-1 $ integers $ x_2,\dots,x_n $ $ (1\le x_i\le 500) $ — the elements of $ x $ .

It is guaranteed that the sum of values $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case output any $ a_1,\dots,a_n $ ( $ 1 \le a_i \le 10^9 $ ) which satisfies the statement.

## 说明/提示

In the first test case $ a=[3,5,4,9] $ satisfies the conditions, because:

- $ a_2\bmod a_1=5\bmod 3=2=x_2 $ ;
- $ a_3\bmod a_2=4\bmod 5=4=x_3 $ ;
- $ a_4\bmod a_3=9\bmod 4=1=x_4 $ ;

## 样例 #1

### 输入

```
5
4
2 4 1
3
1 1
6
4 2 5 1 2
2
500
3
1 5
```

### 输出

```
3 5 4 9
2 5 11
5 14 16 5 11 24
501 500
2 7 5
```

