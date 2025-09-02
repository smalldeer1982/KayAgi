---
title: "DZY Loves Hash"
layout: "post"
diff: 入门
pid: CF447A
tag: []
---

# DZY Loves Hash

## 题目描述

DZY has a hash table with $ p $ buckets, numbered from $ 0 $ to $ p-1 $ . He wants to insert $ n $ numbers, in the order they are given, into the hash table. For the $ i $ -th number $ x_{i} $ , DZY will put it into the bucket numbered $ h(x_{i}) $ , where $ h(x) $ is the hash function. In this problem we will assume, that $ h(x)=x mod p $ . Operation $ a mod b $ denotes taking a remainder after division $ a $ by $ b $ .

However, each bucket can contain no more than one element. If DZY wants to insert an number into a bucket which is already filled, we say a "conflict" happens. Suppose the first conflict happens right after the $ i $ -th insertion, you should output $ i $ . If no conflict happens, just output -1.

## 输入格式

The first line contains two integers, $ p $ and $ n $ $ (2<=p,n<=300) $ . Then $ n $ lines follow. The $ i $ -th of them contains an integer $ x_{i} $ $ (0<=x_{i}<=10^{9}) $ .

## 输出格式

Output a single integer — the answer to the problem.

## 样例 #1

### 输入

```
10 5
0
21
53
41
53

```

### 输出

```
4

```

## 样例 #2

### 输入

```
5 5
0
1
2
3
4

```

### 输出

```
-1

```

