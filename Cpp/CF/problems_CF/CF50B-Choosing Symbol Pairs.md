---
title: "Choosing Symbol Pairs"
layout: "post"
diff: 普及-
pid: CF50B
tag: []
---

# Choosing Symbol Pairs

## 题目描述

There is a given string $ S $ consisting of $ N $ symbols. Your task is to find the number of ordered pairs of integers $ i $ and $ j $ such that

1\. $ 1<=i,j<=N $

2\. $ S[i]=S[j] $ , that is the $ i $ -th symbol of string $ S $ is equal to the $ j $ -th.

## 输入格式

The single input line contains $ S $ , consisting of lowercase Latin letters and digits. It is guaranteed that string $ S $ in not empty and its length does not exceed $ 10^{5} $ .

## 输出格式

Print a single number which represents the number of pairs $ i $ and $ j $ with the needed property. Pairs $ (x,y) $ and $ (y,x) $ should be considered different, i.e. the ordered pairs count.

## 样例 #1

### 输入

```
great10

```

### 输出

```
7

```

## 样例 #2

### 输入

```
aaaaaaaaaa

```

### 输出

```
100

```

