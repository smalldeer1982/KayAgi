---
title: "Permutation Counting"
layout: "post"
diff: 省选/NOI-
pid: CF1671F
tag: []
---

# Permutation Counting

## 题目描述

Calculate the number of permutations $ p $ of size $ n $ with exactly $ k $ inversions (pairs of indices $ (i, j) $ such that $ i < j $ and $ p_i > p_j $ ) and exactly $ x $ indices $ i $ such that $ p_i > p_{i+1} $ .

Yep, that's the whole problem. Good luck!

## 输入格式

The first line contains one integer $ t $ ( $ 1 \le t \le 3 \cdot 10^4 $ ) — the number of test cases.

Each test case consists of one line which contains three integers $ n $ , $ k $ and $ x $ ( $ 1 \le n \le 998244352 $ ; $ 1 \le k \le 11 $ ; $ 1 \le x \le 11 $ ).

## 输出格式

For each test case, print one integer — the answer to the problem, taken modulo $ 998244353 $ .

## 样例 #1

### 输入

```
5
10 6 4
7 3 1
163316 11 7
136373 11 1
325902 11 11
```

### 输出

```
465
12
986128624
7636394
57118194
```

