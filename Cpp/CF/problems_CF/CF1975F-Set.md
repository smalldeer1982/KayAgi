---
title: "Set"
layout: "post"
diff: 省选/NOI-
pid: CF1975F
tag: ['分治']
---

# Set

## 题目描述

Define the binary encoding of a finite set of natural numbers $ T \subseteq \{0,1,2,\ldots\} $ as $ f(T) = \sum\limits_{i \in T} 2^i $ . For example, $ f(\{0,2\}) = 2^0 + 2^2 = 5 $ and $ f(\{\}) = 0 $ . Notice that $ f $ is a bijection from all such sets to all non-negative integers. As such, $ f^{-1} $ is also defined.

You are given an integer $ n $ along with $ 2^n-1 $ sets $ V_1,V_2,\ldots,V_{2^n-1} $ .

Find all sets $ S $ that satisfy the following constraint:

- $ S \subseteq \{0,1,\ldots,n-1\} $ . Note that $ S $ can be empty.
- For all non-empty subsets $ T \subseteq \{0,1,\ldots,n-1\} $ , $ |S \cap T| \in V_{f(T)} $ .

Due to the large input and output, both input and output will be given in terms of binary encodings of the sets.

## 输入格式

The first line of input contains a single integer $ n $ ( $ 1 \leq n \leq 20 $ ).

The second line of input contains $ 2^n-1 $ integers $ v_1,v_2,\ldots,v_{2^n-1} $ ( $ 0 \leq v_i < 2^{n+1} $ ) — the sets $ V_i $ given in their binary encoding where $ V_i = f^{-1}(v_i) $ .

## 输出格式

The first line of output should contain an integer $ k $ indicating the number of possible $ S $ .

In the following $ k $ lines, you should output $ f(S) $ for all possible $ S $ in increasing order.

## 说明/提示

In the first test case, one possible $ S $ is $ f^{-1}(3) = \{0,1\} $ . All the non-empty subsets $ T \subseteq \{0,1,2\} $ and the corresponding $ |S \cap T| $ , $ f(T) $ and $ V_f(T) $ are as follows:

  $ T $  $ |S\cap T| $  $ f(T) $  $ V_{f(T)} $  $ \{0\} $  $ 1 $  $ 1 $  $ \{0,1,2,3\} $  $ \{1\} $  $ 1 $  $ 2 $  $ \{0,1,2,3\} $  $ \{2\} $  $ 0 $  $ 4 $  $ \{0,1,2,3\} $  $ \{0,1\} $  $ 2 $  $ 3 $  $ \{0,1,2,3\} $  $ \{0,2\} $  $ 1 $  $ 5 $  $ \{0,1,2,3\} $  $ \{1,2\} $  $ 1 $  $ 6 $  $ \{0,1,2,3\} $  $ \{0,1,2\} $  $ 2 $  $ 7 $  $ \{2,3\} $

## 样例 #1

### 输入

```
3
15 15 15 15 15 15 12
```

### 输出

```
4
3
5
6
7
```

## 样例 #2

### 输入

```
5
63 63 63 63 6 63 63 63 63 63 63 5 63 63 63 63 63 63 8 63 63 63 63 2 63 63 63 63 63 63 63
```

### 输出

```
1
19
```

