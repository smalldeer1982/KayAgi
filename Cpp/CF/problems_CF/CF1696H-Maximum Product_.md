---
title: "Maximum Product?"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1696H
tag: ['动态规划 DP']
---

# Maximum Product?

## 题目描述

You are given a positive integer $ k $ . For a multiset of integers $ S $ , define $ f(S) $ as the following.

- If the number of elements in $ S $ is less than $ k $ , $ f(S)=0 $ .
- Otherwise, define $ f(S) $ as the maximum product you can get by choosing exactly $ k $ integers from $ S $ .

More formally, let $ |S| $ denote the number of elements in $ S $ . Then,

- If $ |S|<k $ , $ f(S)=0 $ .
- Otherwise, $ f(S)=\max\limits_{T\subseteq S,|T|=k}\left(\prod\limits_{i\in T}i\right) $ .

You are given a multiset of integers, $ A $ . Compute $ \sum\limits_{B\subseteq A} f(B) $ modulo $ 10^9+7 $ .

Note that in this problem, we distinguish the elements by indices instead of values. That is, a multiset consisting of $ n $ elements always has $ 2^n $ distinct subsets regardless of whether some of its elements are equal.

## 输入格式

The first line of input contains two integers $ n $ and $ k $ , where $ n $ is the number of elements in $ A $ ( $ 1\le k\le n\le 600 $ ).

The second line of input contains $ n $ integers $ a_1,a_2,\dots,a_n $ , describing the elements in $ A $ ( $ -10^9\le a_i\le 10^9 $ ).

## 输出格式

Output $ \sum\limits_{B\subseteq A} f(B) $ modulo $ 10^9+7 $ .

## 说明/提示

Consider the first sample. From the definitions we know that

- $ f(\varnothing)=0 $
- $ f(\{-1\})=0 $
- $ f(\{2\})=0 $
- $ f(\{4\})=0 $
- $ f(\{-1,2\})=-2 $
- $ f(\{-1,4\})=-4 $
- $ f(\{2,4\})=8 $
- $ f(\{-1,2,4\})=8 $

So we should print $ (0+0+0+0-2-4+8+8)\bmod (10^9+7)=10 $ .

In the second example, note that although the multiset consists of three same values, it still has $ 8 $ distinct subsets: $ \varnothing,\{1\},\{1\},\{1\},\{1,1\},\{1,1\},\{1,1\},\{1,1,1\} $ .

## 样例 #1

### 输入

```
3 2
-1 2 4
```

### 输出

```
10
```

## 样例 #2

### 输入

```
3 1
1 1 1
```

### 输出

```
7
```

## 样例 #3

### 输入

```
10 4
-24 -41 9 -154 -56 14 18 53 -7 120
```

### 输出

```
225905161
```

## 样例 #4

### 输入

```
15 5
0 0 2 -2 2 -2 3 -3 -3 4 5 -4 -4 4 5
```

### 输出

```
18119684
```

