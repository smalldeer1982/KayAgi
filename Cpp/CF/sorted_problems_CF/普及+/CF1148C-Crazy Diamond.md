---
title: "Crazy Diamond"
layout: "post"
diff: 普及+/提高
pid: CF1148C
tag: []
---

# Crazy Diamond

## 题目描述

You are given a permutation $ p $ of integers from $ 1 $ to $ n $ , where $ n $ is an even number.

Your goal is to sort the permutation. To do so, you can perform zero or more operations of the following type:

- take two indices $ i $ and $ j $ such that $ 2 \cdot |i - j| \geq n $ and swap $ p_i $ and $ p_j $ .

There is no need to minimize the number of operations, however you should use no more than $ 5 \cdot n $ operations. One can show that it is always possible to do that.

## 输入格式

The first line contains a single integer $ n $ ( $ 2 \leq n \leq 3 \cdot 10^5 $ , $ n $ is even) — the length of the permutation.

The second line contains $ n $ distinct integers $ p_1, p_2, \ldots, p_n $ ( $ 1 \le p_i \le n $ ) — the given permutation.

## 输出格式

On the first line print $ m $ ( $ 0 \le m \le 5 \cdot n $ ) — the number of swaps to perform.

Each of the following $ m $ lines should contain integers $ a_i, b_i $ ( $ 1 \le a_i, b_i \le n $ , $ |a_i - b_i| \ge \frac{n}{2} $ ) — the indices that should be swapped in the corresponding swap.

Note that there is no need to minimize the number of operations. We can show that an answer always exists.

## 说明/提示

In the first example, when one swap elements on positions $ 1 $ and $ 2 $ , the array becomes sorted.

In the second example, pay attention that there is no need to minimize number of swaps.

In the third example, after swapping elements on positions $ 1 $ and $ 5 $ the array becomes: $ [4, 5, 3, 1, 2, 6] $ . After swapping elements on positions $ 2 $ and $ 5 $ the array becomes $ [4, 2, 3, 1, 5, 6] $ and finally after swapping elements on positions $ 1 $ and $ 4 $ the array becomes sorted: $ [1, 2, 3, 4, 5, 6] $ .

## 样例 #1

### 输入

```
2
2 1

```

### 输出

```
1
1 2
```

## 样例 #2

### 输入

```
4
3 4 1 2

```

### 输出

```
4
1 4
1 4
1 3
2 4

```

## 样例 #3

### 输入

```
6
2 5 3 1 4 6

```

### 输出

```
3
1 5
2 5
1 4

```

