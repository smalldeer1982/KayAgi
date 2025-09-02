---
title: "Summation Game"
layout: "post"
diff: 普及-
pid: CF1920B
tag: []
---

# Summation Game

## 题目描述

Alice and Bob are playing a game. They have an array $ a_1, a_2,\ldots,a_n $ . The game consists of two steps:

- First, Alice will remove at most $ k $ elements from the array.
- Second, Bob will multiply at most $ x $ elements of the array by $ -1 $ .

Alice wants to maximize the sum of elements of the array while Bob wants to minimize it. Find the sum of elements of the array after the game if both players play optimally.

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains three integers $ n $ , $ k $ , and $ x $ ( $ 1 \leq n \leq 2 \cdot 10^5 $ , $ 1 \leq x,k \leq n $ ) — the number of elements in the array, the limit on the number of elements of the array that Alice can remove, and the limit on the number of elements of the array that Bob can multiply $ -1 $ to.

The second line of each test case contains $ n $ integers $ a_1, a_2,\ldots, a_n $ ( $ 1 \leq a_i \leq 1000 $ ) — the elements of the array.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single integer — the sum of elements of the array after the game if both players play optimally.

## 说明/提示

In the first test case, it is optimal for Alice to remove the only element of the array. Then, the sum of elements of the array is $ 0 $ after the game is over.

In the second test case, it is optimal for Alice to not remove any elements. Bob will then multiply $ 4 $ by $ -1 $ . So the final sum of elements of the array is $ 3+1+2-4=2 $ .

In the fifth test case, it is optimal for Alice to remove $ 9, 9 $ . Bob will then multiply $ 5, 5, 3 $ by $ -1 $ . So the final sum of elements of the array is $ -5-5-3+3+3+2=-5 $ .

## 样例 #1

### 输入

```
8
1 1 1
1
4 1 1
3 1 2 4
6 6 3
1 4 3 2 5 6
6 6 1
3 7 3 3 32 15
8 5 3
5 5 3 3 3 2 9 9
10 6 4
1 8 2 9 3 3 4 5 3 200
2 2 1
4 3
2 1 2
1 3
```

### 输出

```
0
2
0
3
-5
-9
0
-1
```

