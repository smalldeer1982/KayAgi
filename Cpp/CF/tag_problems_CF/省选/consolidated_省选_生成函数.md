---
title: "The Child and Binary Tree"
layout: "post"
diff: 省选/NOI-
pid: CF438E
tag: ['生成函数']
---

# The Child and Binary Tree

## 题目描述

Our child likes computer science very much, especially he likes binary trees.

Consider the sequence of $ n $ distinct positive integers: $ c_{1},c_{2},...,c_{n} $ . The child calls a vertex-weighted rooted binary tree good if and only if for every vertex $ v $ , the weight of $ v $ is in the set $ {c_{1},c_{2},...,c_{n}} $ . Also our child thinks that the weight of a vertex-weighted tree is the sum of all vertices' weights.

Given an integer $ m $ , can you for all $ s $ $ (1<=s<=m) $ calculate the number of good vertex-weighted rooted binary trees with weight $ s $ ? Please, check the samples for better understanding what trees are considered different.

We only want to know the answer modulo $ 998244353 $ ( $ 7×17×2^{23}+1 $ , a prime number).

## 输入格式

The first line contains two integers $ n,m $ $ (1<=n<=10^{5}; 1<=m<=10^{5}) $ . The second line contains $ n $ space-separated pairwise distinct integers $ c_{1},c_{2},...,c_{n} $ . $ (1<=c_{i}<=10^{5}) $ .

## 输出格式

Print $ m $ lines, each line containing a single integer. The $ i $ -th line must contain the number of good vertex-weighted rooted binary trees whose weight exactly equal to $ i $ . Print the answers modulo $ 998244353 $ ( $ 7×17×2^{23}+1 $ , a prime number).

## 说明/提示

In the first example, there are $ 9 $ good vertex-weighted rooted binary trees whose weight exactly equal to $ 3 $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF438E/eac2c310aa15e844747811a6717476e6a022e10e.png)

## 样例 #1

### 输入

```
2 3
1 2

```

### 输出

```
1
3
9

```

## 样例 #2

### 输入

```
3 10
9 4 3

```

### 输出

```
0
0
1
1
0
2
4
2
6
15

```

## 样例 #3

### 输入

```
5 10
13 10 6 4 15

```

### 输出

```
0
0
0
1
0
1
0
2
0
5

```



---

