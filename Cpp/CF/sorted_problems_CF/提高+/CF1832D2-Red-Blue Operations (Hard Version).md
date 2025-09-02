---
title: "Red-Blue Operations (Hard Version)"
layout: "post"
diff: 提高+/省选-
pid: CF1832D2
tag: []
---

# Red-Blue Operations (Hard Version)

## 题目描述

The only difference between easy and hard versions is the maximum values of $ n $ and $ q $ .

You are given an array, consisting of $ n $ integers. Initially, all elements are red.

You can apply the following operation to the array multiple times. During the $ i $ -th operation, you select an element of the array; then:

- if the element is red, it increases by $ i $ and becomes blue;
- if the element is blue, it decreases by $ i $ and becomes red.

The operations are numbered from $ 1 $ , i. e. during the first operation some element is changed by $ 1 $ and so on.

You are asked $ q $ queries of the following form:

- given an integer $ k $ , what can the largest minimum in the array be if you apply exactly $ k $ operations to it?

Note that the operations don't affect the array between queries, all queries are asked on the initial array $ a $ .

## 输入格式

The first line contains two integers $ n $ and $ q $ ( $ 1 \le n, q \le 2 \cdot 10^5 $ ) — the number of elements in the array and the number of queries.

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 10^9 $ ).

The third line contains $ q $ integers $ k_1, k_2, \dots, k_q $ ( $ 1 \le k_j \le 10^9 $ ).

## 输出格式

For each query, print a single integer — the largest minimum that the array can have after you apply exactly $ k $ operations to it.

## 样例 #1

### 输入

```
4 10
5 2 8 4
1 2 3 4 5 6 7 8 9 10
```

### 输出

```
3 4 5 6 7 8 8 10 8 12
```

## 样例 #2

### 输入

```
5 10
5 2 8 4 4
1 2 3 4 5 6 7 8 9 10
```

### 输出

```
3 4 5 6 7 8 9 8 11 8
```

## 样例 #3

### 输入

```
2 5
2 3
10 6 8 1 3
```

### 输出

```
10 7 8 3 3
```

