---
title: "Maximum And Queries (hard version)"
layout: "post"
diff: 提高+/省选-
pid: CF1903D2
tag: []
---

# Maximum And Queries (hard version)

## 题目描述

This is the hard version of the problem. The only difference between the two versions is the constraint on $ n $ and $ q $ , the memory and time limits. You can make hacks only if all versions of the problem are solved.

Theofanis really likes to play with the bits of numbers. He has an array $ a $ of size $ n $ and an integer $ k $ . He can make at most $ k $ operations in the array. In each operation, he picks a single element and increases it by $ 1 $ .

He found the maximum [bitwise AND](https://en.wikipedia.org/wiki/Bitwise_operation#AND) that array $ a $ can have after at most $ k $ operations.

Theofanis has put a lot of work into finding this value and was very happy with his result. Unfortunately, Adaś, being the evil person that he is, decided to bully him by repeatedly changing the value of $ k $ .

Help Theofanis by calculating the maximum possible [bitwise AND](https://en.wikipedia.org/wiki/Bitwise_operation#AND) for $ q $ different values of $ k $ . Note that queries are independent.

## 输入格式

The first line contains two integers $ n $ and $ q $ ( $ 1 \le n, q \le 10^6 $ ) — the size of the array and the number of queries.

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \le a_i \le 10^6 $ ) — the elements of the array.

Next $ q $ lines describe the queries. The $ i $ -th line contains one integer $ k_i $ ( $ 0 \le k_i \le 10^{18} $ ) — the number of operations that can be done in the $ i $ -th query.

## 输出格式

For each query, print one integer — the maximum bitwise AND that array $ a $ can have after at most $ k_i $ operations.

## 说明/提示

In the first test case, in the first query, we add $ 1 $ in the first and last elements of the array.

Thus, the array becomes $ [2,3,7,6] $ with bitwise AND equal to $ 2 $ .

In the second test case, in the first query, we add $ 1 $ in the first element, $ 5 $ in the second, and $ 3 $ in the third and now all the elements are equal to $ 5 $ .

## 样例 #1

### 输入

```
4 2
1 3 7 5
2
10
```

### 输出

```
2
6
```

## 样例 #2

### 输入

```
3 5
4 0 2
9
8
17
1
3
```

### 输出

```
5
4
7
0
1
```

## 样例 #3

### 输入

```
1 2
10
5
2318381298321
```

### 输出

```
15
2318381298331
```

