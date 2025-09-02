---
title: "Deterministic Heap (Hard Version)"
layout: "post"
diff: 省选/NOI-
pid: CF2001E2
tag: ['动态规划 DP']
---

# Deterministic Heap (Hard Version)

## 题目描述

This is the hard version of the problem. The difference between the two versions is the definition of deterministic max-heap, time limit, and constraints on $ n $ and $ t $ . You can make hacks only if both versions of the problem are solved.

Consider a perfect binary tree with size $ 2^n - 1 $ , with nodes numbered from $ 1 $ to $ 2^n-1 $ and rooted at $ 1 $ . For each vertex $ v $ ( $ 1 \le v \le 2^{n - 1} - 1 $ ), vertex $ 2v $ is its left child and vertex $ 2v + 1 $ is its right child. Each node $ v $ also has a value $ a_v $ assigned to it.

Define the operation $ \mathrm{pop} $ as follows:

1. initialize variable $ v $ as $ 1 $ ;
2. repeat the following process until vertex $ v $ is a leaf (i.e. until $ 2^{n - 1} \le v \le 2^n - 1 $ ); 
  1. among the children of $ v $ , choose the one with the larger value on it and denote such vertex as $ x $ ; if the values on them are equal (i.e. $ a_{2v} = a_{2v + 1} $ ), you can choose any of them;
  2. assign $ a_x $ to $ a_v $ (i.e. $ a_v := a_x $ );
  3. assign $ x $ to $ v $ (i.e. $ v := x $ );
3. assign $ -1 $ to $ a_v $ (i.e. $ a_v := -1 $ ).

Then we say the $ \mathrm{pop} $ operation is deterministic if there is a unique way to do such operation. In other words, $ a_{2v} \neq a_{2v + 1} $ would hold whenever choosing between them.

A binary tree is called a max-heap if for every vertex $ v $ ( $ 1 \le v \le 2^{n - 1} - 1 $ ), both $ a_v \ge a_{2v} $ and $ a_v \ge a_{2v + 1} $ hold.

A max-heap is deterministic if the $ \mathrm{pop} $ operation is deterministic to the heap when we do it for the first and the second time.

Initially, $ a_v := 0 $ for every vertex $ v $ ( $ 1 \le v \le 2^n - 1 $ ), and your goal is to count the number of different deterministic max-heaps produced by applying the following operation $ \mathrm{add} $ exactly $ k $ times:

- Choose an integer $ v $ ( $ 1 \le v \le 2^n - 1 $ ) and, for every vertex $ x $ on the path between $ 1 $ and $ v $ , add $ 1 $ to $ a_x $ .

Two heaps are considered different if there is a node which has different values in the heaps.

Since the answer might be large, print it modulo $ p $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 50 $ ). The description of the test cases follows.

The first line of each test case contains three integers $ n, k, p $ ( $ 2 \le n \le 100 $ , $ 1 \le k \le 500 $ , $ 10^8 \le p \le 10^9 $ , $ p $ is a prime).

It is guaranteed that the sum of $ n $ does not exceed $ 100 $ and the sum of $ k $ over all test cases does not exceed $ 500 $ .

## 输出格式

For each test case, output a single line containing an integer: the number of different deterministic max-heaps produced by applying the aforementioned operation $ \mathrm{add} $ exactly $ k $ times, modulo $ p $ .

## 说明/提示

For the first testcase, if we choose $ v = 1 $ and do the operation, we would have $ a = [1, 0, 0] $ , and since $ a_2 = a_3 $ , we can choose either of them when doing the first $ \mathrm{pop} $ operation, so such heap is not a deterministic max-heap.

And if we choose $ v = 2 $ , we would have $ a = [1, 1, 0] $ , during the first $ \mathrm{pop} $ , the following would happen:

- initialize $ v $ as $ 1 $
- since $ a_{2v} > a_{2v + 1} $ , choose $ 2v $ as $ x $ , then $ x = 2 $
- assign $ a_x $ to $ a_v $ , then $ a = [1, 1, 0] $
- assign $ x $ to $ v $ , then $ v = 2 $
- since $ v $ is a leaf, assign $ -1 $ to $ a_v $ , then $ a = [1, -1, 0] $

And during the second $ \mathrm{pop} $ , the following would happen:

- initialize $ v $ as $ 1 $
- since $ a_{2v} < a_{2v + 1} $ , choose $ 2v + 1 $ as $ x $ , then $ x = 3 $
- assign $ a_x $ to $ a_v $ , then $ a = [0, -1, 0] $
- assign $ x $ to $ v $ , then $ v = 3 $
- since $ v $ is a leaf, assign $ -1 $ to $ a_v $ , then $ a = [0, -1, -1] $

Since both the first and the second $ \mathrm{pop} $ operation are deterministic, this is a deterministic max-heap. Also, if we choose $ v = 3 $ , $ a $ would be a deterministic max-heap, so the answer is $ 2 $ .

## 样例 #1

### 输入

```
6
2 1 998244353
3 2 998244853
3 3 998244353
3 4 100000037
4 2 100000039
4 3 100000037
```

### 输出

```
2
12
40
100
32
224
```

## 样例 #2

### 输入

```
1
100 500 100000037
```

### 输出

```
66681128
```

## 样例 #3

### 输入

```
2
87 63 100000037
13 437 100000039
```

### 输出

```
83566569
54517140
```

