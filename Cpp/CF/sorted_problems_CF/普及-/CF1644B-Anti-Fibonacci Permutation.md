---
title: "Anti-Fibonacci Permutation"
layout: "post"
diff: 普及-
pid: CF1644B
tag: []
---

# Anti-Fibonacci Permutation

## 题目描述

Let's call a permutation $ p $ of length $ n $ anti-Fibonacci if the condition $ p_{i-2} + p_{i-1} \ne p_i $ holds for all $ i $ ( $ 3 \le i \le n $ ). Recall that the permutation is the array of length $ n $ which contains each integer from $ 1 $ to $ n $ exactly once.

Your task is for a given number $ n $ print $ n $ distinct anti-Fibonacci permutations of length $ n $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 48 $ ) — the number of test cases.

The single line of each test case contains a single integer $ n $ ( $ 3 \le n \le 50 $ ).

## 输出格式

For each test case, print $ n $ lines. Each line should contain an anti-Fibonacci permutation of length $ n $ . In each test case, you cannot print any permutation more than once.

If there are multiple answers, print any of them. It can be shown that it is always possible to find $ n $ different anti-Fibonacci permutations of size $ n $ under the constraints of the problem.

## 样例 #1

### 输入

```
2
4
3
```

### 输出

```
4 1 3 2
1 2 4 3
3 4 1 2
2 4 1 3
3 2 1
1 3 2
3 1 2
```

