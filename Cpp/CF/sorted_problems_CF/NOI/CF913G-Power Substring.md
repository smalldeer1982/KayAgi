---
title: "Power Substring"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF913G
tag: []
---

# Power Substring

## 题目描述

You are given $ n $ positive integers $ a_{1},a_{2},...,a_{n} $ .

For every $ a_{i} $ you need to find a positive integer $ k_{i} $ such that the decimal notation of $ 2^{k_{i}} $ contains the decimal notation of $ a_{i} $ as a substring among its last $ min(100,length(2^{k_{i}})) $ digits. Here $ length(m) $ is the length of the decimal notation of $ m $ .

Note that you don't have to minimize $ k_{i} $ . The decimal notations in this problem do not contain leading zeros.

## 输入格式

The first line contains a single integer $ n $ ( $ 1<=n<=2000 $ ) — the number of integers $ a_{i} $ .

Each of the next $ n $ lines contains a positive integer $ a_{i} $ ( $ 1<=a_{i}<10^{11} $ ).

## 输出格式

Print $ n $ lines. The $ i $ -th of them should contain a positive integer $ k_{i} $ such that the last $ min(100,length(2^{k_{i}})) $ digits of $ 2^{k_{i}} $ contain the decimal notation of $ a_{i} $ as a substring. Integers $ k_{i} $ must satisfy $ 1<=k_{i}<=10^{50} $ .

It can be shown that the answer always exists under the given constraints. If there are multiple answers, print any of them.

## 样例 #1

### 输入

```
2
8
2

```

### 输出

```
3
1

```

## 样例 #2

### 输入

```
2
3
4857

```

### 输出

```
5
20

```

