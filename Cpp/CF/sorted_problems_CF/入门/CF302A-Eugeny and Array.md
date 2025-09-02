---
title: "Eugeny and Array"
layout: "post"
diff: 入门
pid: CF302A
tag: []
---

# Eugeny and Array

## 题目描述

Eugeny has array $ a=a_{1},a_{2},...,a_{n} $ , consisting of $ n $ integers. Each integer $ a_{i} $ equals to -1, or to 1. Also, he has $ m $ queries:

- Query number $ i $ is given as a pair of integers $ l_{i} $ , $ r_{i} $ $ (1<=l_{i}<=r_{i}<=n) $ .
- The response to the query will be integer $ 1 $ , if the elements of array $ a $ can be rearranged so as the sum $ a_{li}+a_{li}+1+...+a_{ri}=0 $ , otherwise the response to the query will be integer $ 0 $ .

Help Eugeny, answer all his queries.

## 输入格式

The first line contains integers $ n $ and $ m $ $ (1<=n,m<=2·10^{5}) $ . The second line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ $ (a_{i}= $ - $ 1,1) $ . Next $ m $ lines contain Eugene's queries. The $ i $ -th line contains integers $ l_{i},r_{i} $ $ (1<=l_{i}<=r_{i}<=n) $ .

## 输出格式

Print $ m $ integers — the responses to Eugene's queries in the order they occur in the input.

## 样例 #1

### 输入

```
2 3
1 -1
1 1
1 2
2 2

```

### 输出

```
0
1
0

```

## 样例 #2

### 输入

```
5 5
-1 1 1 1 -1
1 1
2 3
3 5
2 5
1 5

```

### 输出

```
0
1
0
1
0

```

