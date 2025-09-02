---
title: "Fibonacci-ish II"
layout: "post"
diff: 省选/NOI-
pid: CF633H
tag: []
---

# Fibonacci-ish II

## 题目描述

Yash is finally tired of computing the length of the longest Fibonacci-ish sequence. He now plays around with more complex things such as Fibonacci-ish potentials.

Fibonacci-ish potential of an array $ a_{i} $ is computed as follows:

1. Remove all elements $ j $ if there exists $ i&lt;j $ such that $ a_{i}=a_{j} $ .
2. Sort the remaining elements in ascending order, i.e. $ a_{1}&lt;a_{2}&lt;...&lt;a_{n} $ .
3. Compute the potential as $ P(a)=a_{1}·F_{1}+a_{2}·F_{2}+...+a_{n}·F_{n} $ , where $ F_{i} $ is the $ i $ -th Fibonacci number (see notes for clarification).

You are given an array $ a_{i} $ of length $ n $ and $ q $ ranges from $ l_{j} $ to $ r_{j} $ . For each range $ j $ you have to compute the Fibonacci-ish potential of the array $ b_{i} $ , composed using all elements of $ a_{i} $ from $ l_{j} $ to $ r_{j} $ inclusive. Find these potentials modulo $ m $ .

## 输入格式

The first line of the input contains integers of $ n $ and $ m $ ( $ 1<=n,m<=30000 $ ) — the length of the initial array and the modulo, respectively.

The next line contains $ n $ integers $ a_{i} $ ( $ 0<=a_{i}<=10^{9} $ ) — elements of the array.

Then follow the number of ranges $ q $ ( $ 1<=q<=30000 $ ).

Last $ q $ lines contain pairs of indices $ l_{i} $ and $ r_{i} $ ( $ 1<=l_{i}<=r_{i}<=n $ ) — ranges to compute Fibonacci-ish potentials.

## 输出格式

Print $ q $ lines, $ i $ -th of them must contain the Fibonacci-ish potential of the $ i $ -th range modulo $ m $ .

## 说明/提示

For the purpose of this problem define Fibonacci numbers as follows:

1. $ F_{1}=F_{2}=1 $ .
2. $ F_{n}=F_{n-1}+F_{n-2} $ for each $ n&gt;2 $ .

In the first query, the subarray \[1,2,1\] can be formed using the minimal set {1,2}. Thus, the potential of this subarray is 1\*1+2\*1=3.

## 样例 #1

### 输入

```
5 10
2 1 2 1 2
2
2 4
4 5

```

### 输出

```
3
3

```

