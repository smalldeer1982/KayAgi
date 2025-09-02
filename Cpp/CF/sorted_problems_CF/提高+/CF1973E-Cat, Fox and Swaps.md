---
title: "Cat, Fox and Swaps"
layout: "post"
diff: 提高+/省选-
pid: CF1973E
tag: ['贪心']
---

# Cat, Fox and Swaps

## 题目描述

Fox has found an array $ p_1, p_2, \ldots, p_n $ , that is a permutation of length $ n^\dagger $ of the numbers $ 1, 2, \ldots, n $ . She wants to sort the elements in increasing order. Cat wants to help her — he is able to swap any two numbers $ x $ and $ y $ in the array, but only if $ l \leq x + y \leq r $ (note that the constraint is imposed on the values of the elements, not their positions). He can make such swaps any number of times.

They don't know the numbers $ l $ , $ r $ yet, they only know that it's true that $ 1 \leq l \leq r \leq 2 \cdot n $ .

You are given the number $ n $ and the array $ p_1, p_2, \ldots, p_n $ . Determine how many pairs $ (l, r) $ satisfying the conditions are there such that you can sort the permutation if you can only swap two number $ (x, y) $ such that $ l \leq x + y \leq r $ (arbitrary number of times, possibly $ 0 $ ).

 $ ^\dagger $ A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

Description of each test case consists of two lines. The first line contains one integer $ n $ ( $ 1 \leq n \leq 10^5 $ ).

The second line contains $ n $ integers: the array $ p_1, p_2, \ldots, p_n $ ( $ 1 \le p_i \le n $ ). It is guaranteed that this array is a permutation of length $ n $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, print the number of pairs of integers $ (l, r) $ such that $ 1 \leq l \leq r \leq 2 \cdot n $ , and you can sort the array under the constraints.

## 说明/提示

In the first example, we need to be able to swap $ 1 $ and $ 2 $ , so we must be able to swap numbers with sum $ 3 $ . There are exactly $ 6 $ pairs satisfying the condition: $ (1, 3), (2, 3), (3, 3), (1, 4), (2, 4) $ and $ (3, 4) $ , so the answer is $ 6 $ .

In the second example, the $ 11 $ pairs satisfying the condition are $ (1, 4), (1, 5), (1, 6), (2, 4), (2, 5), (2, 6), (3, 4), (3, 5), (3, 6), (4, 5) $ and $ (4, 6) $ . For example, if we pick the pair $ (3, 4) $ we can first swap the numbers $ 1 $ and $ 2 $ and then the numbers $ 1 $ and $ 3 $ , after this, the permutation is sorted.

## 样例 #1

### 输入

```
7
2
2 1
3
3 1 2
4
3 2 1 4
5
5 3 1 2 4
5
1 2 3 4 5
6
3 2 1 5 4 6
6
1 3 2 4 5 6
```

### 输出

```
6
11
23
29
55
46
58
```

