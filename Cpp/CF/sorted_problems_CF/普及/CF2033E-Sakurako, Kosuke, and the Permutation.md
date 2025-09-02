---
title: "Sakurako, Kosuke, and the Permutation"
layout: "post"
diff: 普及/提高-
pid: CF2033E
tag: ['贪心']
---

# Sakurako, Kosuke, and the Permutation

## 题目描述

Sakurako's exams are over, and she did excellently. As a reward, she received a permutation $ p $ . Kosuke was not entirely satisfied because he failed one exam and did not receive a gift. He decided to sneak into her room (thanks to the code for her lock) and spoil the permutation so that it becomes simple.

A permutation $ p $ is considered simple if for every $ i $ $ (1\le i \le n) $ one of the following conditions holds:

- $ p_i=i $
- $ p_{p_i}=i $

For example, the permutations $ [1, 2, 3, 4] $ , $ [5, 2, 4, 3, 1] $ , and $ [2, 1] $ are simple, while $ [2, 3, 1] $ and $ [5, 2, 1, 4, 3] $ are not.

In one operation, Kosuke can choose indices $ i,j $ $ (1\le i,j\le n) $ and swap the elements $ p_i $ and $ p_j $ .

Sakurako is about to return home. Your task is to calculate the minimum number of operations that Kosuke needs to perform to make the permutation simple.

## 输入格式

The first line contains one integer $ t $ ( $ 1\le t\le 10^4 $ ) — the number of test cases.

Each test case is described by two lines.

- The first line contains one integer $ n $ ( $ 1\le n \le 10^6 $ ) — the length of the permutation $ p $ .
- The second line contains $ n $ integers $ p_i $ ( $ 1\le p_i\le n $ ) — the elements of the permutation $ p $ .

It is guaranteed that the sum of $ n $ across all test cases does not exceed $ 10^6 $ .

It is guaranteed that $ p $ is a permutation.

## 输出格式

For each test case, output the minimum number of operations that Kosuke needs to perform to make the permutation simple.

## 说明/提示

In the first and second examples, the permutations are already simple.

In the fourth example, it is sufficient to swap $ p_2 $ and $ p_4 $ . Thus, the permutation will become $ [2, 1, 4, 3] $ in $ 1 $ operation.

## 样例 #1

### 输入

```
6
5
1 2 3 4 5
5
5 4 3 2 1
5
2 3 4 5 1
4
2 3 4 1
3
1 3 2
7
2 3 1 5 6 7 4
```

### 输出

```
0
0
2
1
0
2
```

