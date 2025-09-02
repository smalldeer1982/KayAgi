---
title: "Machine Learning"
layout: "post"
diff: 省选/NOI-
pid: CF940F
tag: ['莫队', '枚举', '分块']
---

# Machine Learning

## 题目描述

You come home and fell some unpleasant smell. Where is it coming from?

You are given an array $ a $ . You have to answer the following queries:

1. You are given two integers $ l $ and $ r $ . Let $ c_{i} $ be the number of occurrences of $ i $ in $ a_{l:r} $ , where $ a_{l:r} $ is the subarray of $ a $ from $ l $ -th element to $ r $ -th inclusive. Find the Mex of $ {c_{0},c_{1},...,c_{10^{9}}} $
2. You are given two integers $ p $ to $ x $ . Change $ a_{p} $ to $ x $ .

The Mex of a multiset of numbers is the smallest non-negative integer not in the set.

Note that in this problem all elements of $ a $ are positive, which means that $ c_{0} $ = 0 and $ 0 $ is never the answer for the query of the second type.

## 输入格式

The first line of input contains two integers $ n $ and $ q $ ( $ 1<=n,q<=100000 $ ) — the length of the array and the number of queries respectively.

The second line of input contains $ n $ integers — $ a_{1} $ , $ a_{2} $ , $ ... $ , $ a_{n} $ ( $ 1<=a_{i}<=10^{9} $ ).

Each of the next $ q $ lines describes a single query.

The first type of query is described by three integers $ t_{i}=1 $ , $ l_{i} $ , $ r_{i} $ , where $ 1<=l_{i}<=r_{i}<=n $ — the bounds of the subarray.

The second type of query is described by three integers $ t_{i}=2 $ , $ p_{i} $ , $ x_{i} $ , where $ 1<=p_{i}<=n $ is the index of the element, which must be changed and $ 1<=x_{i}<=10^{9} $ is the new value.

## 输出格式

For each query of the first type output a single integer — the Mex of $ {c_{0},c_{1},...,c_{10^{9}}} $ .

## 说明/提示

The subarray of the first query consists of the single element — $ 1 $ .

The subarray of the second query consists of four $ 2 $ s, one $ 3 $ and two $ 1 $ s.

The subarray of the fourth query consists of three $ 1 $ s, three $ 2 $ s and one $ 3 $ .

## 样例 #1

### 输入

```
10 4
1 2 3 1 1 2 2 2 9 9
1 1 1
1 2 8
2 7 1
1 2 8

```

### 输出

```
2
3
2

```

