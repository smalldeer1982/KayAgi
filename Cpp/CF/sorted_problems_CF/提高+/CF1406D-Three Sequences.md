---
title: "Three Sequences"
layout: "post"
diff: 提高+/省选-
pid: CF1406D
tag: []
---

# Three Sequences

## 题目描述

You are given a sequence of $ n $ integers $ a_1, a_2, \ldots, a_n $ .

You have to construct two sequences of integers $ b $ and $ c $ with length $ n $ that satisfy:

- for every $ i $ ( $ 1\leq i\leq n $ ) $ b_i+c_i=a_i $
- $ b $ is non-decreasing, which means that for every $ 1<i\leq n $ , $ b_i\geq b_{i-1} $ must hold
- $ c $ is non-increasing, which means that for every $ 1<i\leq n $ , $ c_i\leq c_{i-1} $ must hold

You have to minimize $ \max(b_i,c_i) $ . In other words, you have to minimize the maximum number in sequences $ b $ and $ c $ .

Also there will be $ q $ changes, the $ i $ -th change is described by three integers $ l,r,x $ . You should add $ x $ to $ a_l,a_{l+1}, \ldots, a_r $ .

You have to find the minimum possible value of $ \max(b_i,c_i) $ for the initial sequence and for sequence after each change.

## 输入格式

The first line contains an integer $ n $ ( $ 1\leq n\leq 10^5 $ ).

The secound line contains $ n $ integers $ a_1,a_2,\ldots,a_n $ ( $ 1\leq i\leq n $ , $ -10^9\leq a_i\leq 10^9 $ ).

The third line contains an integer $ q $ ( $ 1\leq q\leq 10^5 $ ).

Each of the next $ q $ lines contains three integers $ l,r,x $ ( $ 1\leq l\leq r\leq n,-10^9\leq x\leq 10^9 $ ), desribing the next change.

## 输出格式

Print $ q+1 $ lines.

On the $ i $ -th ( $ 1 \leq i \leq q+1 $ ) line, print the answer to the problem for the sequence after $ i-1 $ changes.

## 说明/提示

In the first test:

- The initial sequence $ a = (2, -1, 7, 3) $ . Two sequences $ b=(-3,-3,5,5),c=(5,2,2,-2) $ is a possible choice.
- After the first change $ a = (2, -4, 4, 0) $ . Two sequences $ b=(-3,-3,5,5),c=(5,-1,-1,-5) $ is a possible choice.
- After the second change $ a = (2, -4, 6, 2) $ . Two sequences $ b=(-4,-4,6,6),c=(6,0,0,-4) $ is a possible choice.

## 样例 #1

### 输入

```
4
2 -1 7 3
2
2 4 -3
3 4 2
```

### 输出

```
5
5
6
```

## 样例 #2

### 输入

```
6
-9 -10 -9 -6 -5 4
3
2 6 -9
1 2 -10
4 6 -3
```

### 输出

```
3
3
3
1
```

## 样例 #3

### 输入

```
1
0
2
1 1 -1
1 1 -1
```

### 输出

```
0
0
-1
```

