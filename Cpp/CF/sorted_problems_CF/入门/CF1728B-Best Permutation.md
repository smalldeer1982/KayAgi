---
title: "Best Permutation"
layout: "post"
diff: 入门
pid: CF1728B
tag: []
---

# Best Permutation

## 题目描述

Let's define the value of the permutation $ p $ of $ n $ integers $ 1 $ , $ 2 $ , ..., $ n $ (a permutation is an array where each element from $ 1 $ to $ n $ occurs exactly once) as follows:

- initially, an integer variable $ x $ is equal to $ 0 $ ;
- if $ x < p_1 $ , then add $ p_1 $ to $ x $ (set $ x = x + p_1 $ ), otherwise assign $ 0 $ to $ x $ ;
- if $ x < p_2 $ , then add $ p_2 $ to $ x $ (set $ x = x + p_2 $ ), otherwise assign $ 0 $ to $ x $ ;
- ...
- if $ x < p_n $ , then add $ p_n $ to $ x $ (set $ x = x + p_n $ ), otherwise assign $ 0 $ to $ x $ ;
- the value of the permutation is $ x $ at the end of this process.

For example, for $ p = [4, 5, 1, 2, 3, 6] $ , the value of $ x $ changes as follows: $ 0, 4, 9, 0, 2, 5, 11 $ , so the value of the permutation is $ 11 $ .

You are given an integer $ n $ . Find a permutation $ p $ of size $ n $ with the maximum possible value among all permutations of size $ n $ . If there are several such permutations, you can print any of them.

## 输入格式

The first line contains one integer $ t $ ( $ 1 \le t \le 97 $ ) — the number of test cases.

The only line of each test case contains one integer $ n $ ( $ 4 \le n \le 100 $ ).

## 输出格式

For each test case, print $ n $ integers — the permutation $ p $ of size $ n $ with the maximum possible value among all permutations of size $ n $ .

## 样例 #1

### 输入

```
3
4
5
6
```

### 输出

```
2 1 3 4
1 2 3 4 5
4 5 1 2 3 6
```

