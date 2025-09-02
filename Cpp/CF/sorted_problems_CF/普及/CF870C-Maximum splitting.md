---
title: "Maximum splitting"
layout: "post"
diff: 普及/提高-
pid: CF870C
tag: []
---

# Maximum splitting

## 题目描述

You are given several queries. In the $ i $ -th query you are given a single positive integer $ n_{i} $ . You are to represent $ n_{i} $ as a sum of maximum possible number of composite summands and print this maximum number, or print -1, if there are no such splittings.

An integer greater than $ 1 $ is composite, if it is not prime, i.e. if it has positive divisors not equal to $ 1 $ and the integer itself.

## 输入格式

The first line contains single integer $ q $ ( $ 1<=q<=10^{5} $ ) — the number of queries.

 $ q $ lines follow. The ( $ i+1 $ )-th line contains single integer $ n_{i} $ ( $ 1<=n_{i}<=10^{9} $ ) — the $ i $ -th query.

## 输出格式

For each query print the maximum possible number of summands in a valid splitting to composite summands, or -1, if there are no such splittings.

## 说明/提示

 $ 12=4+4+4=4+8=6+6=12 $ , but the first splitting has the maximum possible number of summands.

 $ 8=4+4 $ , $ 6 $ can't be split into several composite summands.

 $ 1,2,3 $ are less than any composite number, so they do not have valid splittings.

## 样例 #1

### 输入

```
1
12

```

### 输出

```
3

```

## 样例 #2

### 输入

```
2
6
8

```

### 输出

```
1
2

```

## 样例 #3

### 输入

```
3
1
2
3

```

### 输出

```
-1
-1
-1

```

