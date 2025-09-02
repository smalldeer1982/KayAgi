---
title: "Jeff and Removing Periods"
layout: "post"
diff: 提高+/省选-
pid: CF351D
tag: []
---

# Jeff and Removing Periods

## 题目描述

Cosider a sequence, consisting of $ n $ integers: $ a_{1} $ , $ a_{2} $ , $ ... $ , $ a_{n} $ . Jeff can perform the following operation on sequence $ a $ :

- take three integers $ v $ , $ t $ , $ k $ $ (1<=v,t<=n; 0<=k; v+tk<=n) $ , such that $ a_{v} $ = $ a_{v+t} $ , $ a_{v+t} $ = $ a_{v+2t} $ , $ ... $ , $ a_{v+t(k-1)} $ = $ a_{v+tk} $ ;
- remove elements $ a_{v} $ , $ a_{v+t} $ , $ ... $ , $ a_{v+t·k} $ from the sequence $ a $ , the remaining elements should be reindexed $ a_{1},a_{2},...,a_{n-k-1} $ .
- permute in some order the remaining elements of sequence $ a $ .

A beauty of a sequence $ a $ is the minimum number of operations that is needed to delete all elements from sequence $ a $ .

Jeff's written down a sequence of $ m $ integers $ b_{1} $ , $ b_{2} $ , $ ... $ , $ b_{m} $ . Now he wants to ask $ q $ questions. Each question can be described with two integers $ l_{i},r_{i} $ . The answer to the question is the beauty of sequence $ b_{li} $ , $ b_{li}+1 $ , $ ... $ , $ b_{ri} $ . You are given the sequence $ b $ and all questions. Help Jeff, answer all his questions.

## 输入格式

The first line contains integer $ m $ $ (1<=m<=10^{5}) $ . The next line contains $ m $ integers $ b_{1} $ , $ b_{2} $ , $ ... $ , $ b_{m} $ $ (1<=b_{i}<=10^{5}) $ .

The third line contains integer $ q $ $ (1<=q<=10^{5}) $ — the number of questions. The next $ q $ lines contain pairs of integers, $ i $ -th of them contains a pair of integers $ l_{i} $ , $ r_{i} $ $ (1<=l_{i}<=r_{i}<=m) $ — the description of $ i $ -th question.

## 输出格式

In $ q $ lines print the answers to Jeff's queries. Print the answers according to the order of questions in input.

## 样例 #1

### 输入

```
5
2 2 1 1 2
5
1 5
1 1
2 2
1 3
2 3

```

### 输出

```
2
1
1
2
2

```

## 样例 #2

### 输入

```
10
2 1 3 3 3 3 1 3 1 1
10
4 8
2 10
1 10
4 4
1 3
2 4
6 7
1 9
2 5
1 1

```

### 输出

```
2
3
3
1
3
2
2
3
2
1

```

