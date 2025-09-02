---
title: "Two permutations"
layout: "post"
diff: 省选/NOI-
pid: CF323C
tag: []
---

# Two permutations

## 题目描述

You are given two permutations $ p $ and $ q $ , consisting of $ n $ elements, and $ m $ queries of the form: $ l_{1},r_{1},l_{2},r_{2} $ $ (l_{1}<=r_{1}; l_{2}<=r_{2}) $ . The response for the query is the number of such integers from $ 1 $ to $ n $ , that their position in the first permutation is in segment $ [l_{1},r_{1}] $ (borders included), and position in the second permutation is in segment $ [l_{2},r_{2}] $ (borders included too).

A permutation of $ n $ elements is the sequence of $ n $ distinct integers, each not less than $ 1 $ and not greater than $ n $ .

Position of number $ v $ $ (1<=v<=n) $ in permutation $ g_{1},g_{2},...,g_{n} $ is such number $ i $ , that $ g_{i}=v $ .

## 输入格式

The first line contains one integer $ n\ (1<=n<=10^{6}) $ , the number of elements in both permutations. The following line contains $ n $ integers, separated with spaces: $ p_{1},p_{2},...,p_{n}\ (1<=p_{i}<=n) $ . These are elements of the first permutation. The next line contains the second permutation $ q_{1},q_{2},...,q_{n} $ in same format.

The following line contains an integer $ m\ (1<=m<=2·10^{5}) $ , that is the number of queries.

The following $ m $ lines contain descriptions of queries one in a line. The description of the $ i $ -th query consists of four integers: $ a,b,c,d\ (1<=a,b,c,d<=n) $ . Query parameters $ l_{1},r_{1},l_{2},r_{2} $ are obtained from the numbers $ a,b,c,d $ using the following algorithm:

1. Introduce variable $ x $ . If it is the first query, then the variable equals $ 0 $ , else it equals the response for the previous query plus one.
2. Introduce function $ f(z)=((z-1+x)\ mod\ n)+1 $ .
3. Suppose $ l_{1}=min(f(a),f(b)),r_{1}=max(f(a),f(b)),l_{2}=min(f(c),f(d)),r_{2}=max(f(c),f(d)) $ .

## 输出格式

Print a response for each query in a separate line.

## 样例 #1

### 输入

```
3
3 1 2
3 2 1
1
1 2 3 3

```

### 输出

```
1

```

## 样例 #2

### 输入

```
4
4 3 2 1
2 3 4 1
3
1 2 3 4
1 3 2 1
1 4 2 3

```

### 输出

```
1
1
2

```

