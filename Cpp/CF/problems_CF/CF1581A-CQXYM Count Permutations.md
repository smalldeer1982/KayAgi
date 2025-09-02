---
title: "CQXYM Count Permutations"
layout: "post"
diff: 普及-
pid: CF1581A
tag: []
---

# CQXYM Count Permutations

## 题目描述

CQXYM is counting permutations length of $ 2n $ .

A permutation is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array) and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

A permutation $ p $ (length of $ 2n $ ) will be counted only if the number of $ i $ satisfying $ p_i<p_{i+1} $ is no less than $ n $ . For example:

- Permutation $ [1, 2, 3, 4] $ will count, because the number of such $ i $ that $ p_i<p_{i+1} $ equals $ 3 $ ( $ i = 1 $ , $ i = 2 $ , $ i = 3 $ ).
- Permutation $ [3, 2, 1, 4] $ won't count, because the number of such $ i $ that $ p_i<p_{i+1} $ equals $ 1 $ ( $ i = 3 $ ).

CQXYM wants you to help him to count the number of such permutations modulo $ 1000000007 $ ( $ 10^9+7 $ ).

In addition, [modulo operation](https://en.wikipedia.org/wiki/Modulo_operation) is to get the remainder. For example:

- $ 7 \mod 3=1 $ , because $ 7 = 3 \cdot 2 + 1 $ ,
- $ 15 \mod 4=3 $ , because $ 15 = 4 \cdot 3 + 3 $ .

## 输入格式

The input consists of multiple test cases.

The first line contains an integer $ t (t \geq 1) $ — the number of test cases. The description of the test cases follows.

Only one line of each test case contains an integer $ n(1 \leq n \leq 10^5) $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $

## 输出格式

For each test case, print the answer in a single line.

## 说明/提示

$ n=1 $ , there is only one permutation that satisfies the condition: $ [1,2]. $

In permutation $ [1,2] $ , $ p_1<p_2 $ , and there is one $ i=1 $ satisfy the condition. Since $ 1 \geq n $ , this permutation should be counted. In permutation $ [2,1] $ , $ p_1>p_2 $ . Because $ 0<n $ , this permutation should not be counted.

 $ n=2 $ , there are $ 12 $ permutations: $ [1,2,3,4],[1,2,4,3],[1,3,2,4],[1,3,4,2],[1,4,2,3],[2,1,3,4],[2,3,1,4],[2,3,4,1],[2,4,1,3],[3,1,2,4],[3,4,1,2],[4,1,2,3]. $

## 样例 #1

### 输入

```
4
1
2
9
91234
```

### 输出

```
1
12
830455698
890287984
```

