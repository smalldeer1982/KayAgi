---
title: "Drawing Circles is Fun"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF372E
tag: []
---

# Drawing Circles is Fun

## 题目描述

There are a set of points $ S $ on the plane. This set doesn't contain the origin $ O(0,0) $ , and for each two distinct points in the set $ A $ and $ B $ , the triangle $ OAB $ has strictly positive area.

Consider a set of pairs of points $ (P_{1},P_{2}),(P_{3},P_{4}),...,(P_{2k-1},P_{2k}) $ . We'll call the set good if and only if:

- $ k>=2 $ .
- All $ P_{i} $ are distinct, and each $ P_{i} $ is an element of $ S $ .
- For any two pairs $ (P_{2i-1},P_{2i}) $ and $ (P_{2j-1},P_{2j}) $ , the circumcircles of triangles $ OP_{2i-1}P_{2j-1} $ and $ OP_{2i}P_{2j} $ have a single common point, and the circumcircle of triangles $ OP_{2i-1}P_{2j} $ and $ OP_{2i}P_{2j-1} $ have a single common point.

Calculate the number of good sets of pairs modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 输入格式

The first line contains a single integer $ n $ $ (1<=n<=1000) $ — the number of points in $ S $ . Each of the next $ n $ lines contains four integers $ a_{i},b_{i},c_{i},d_{i} $ $ (0<=|a_{i}|,|c_{i}|<=50; 1<=b_{i},d_{i}<=50; (a_{i},c_{i})≠(0,0)) $ . These integers represent a point ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF372E/617f303adacabe28ace76ac72aefdf3264b1fbfa.png).

No two points coincide.

## 输出格式

Print a single integer — the answer to the problem modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 样例 #1

### 输入

```
10
-46 46 0 36
0 20 -24 48
-50 50 -49 49
-20 50 8 40
-15 30 14 28
4 10 -4 5
6 15 8 10
-20 50 -3 15
4 34 -16 34
16 34 2 17

```

### 输出

```
2

```

## 样例 #2

### 输入

```
10
30 30 -26 26
0 15 -36 36
-28 28 -34 34
10 10 0 4
-8 20 40 50
9 45 12 30
6 15 7 35
36 45 -8 20
-16 34 -4 34
4 34 8 17

```

### 输出

```
4

```

## 样例 #3

### 输入

```
10
0 20 38 38
-30 30 -13 13
-11 11 16 16
30 30 0 37
6 30 -4 10
6 15 12 15
-4 5 -10 25
-16 20 4 10
8 17 -2 17
16 34 2 17

```

### 输出

```
10

```

