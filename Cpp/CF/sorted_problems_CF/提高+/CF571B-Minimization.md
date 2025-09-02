---
title: "Minimization"
layout: "post"
diff: 提高+/省选-
pid: CF571B
tag: []
---

# Minimization

## 题目描述

You've got array $ A $ , consisting of $ n $ integers and a positive integer $ k $ . Array $ A $ is indexed by integers from $ 1 $ to $ n $ .

You need to permute the array elements so that value

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF571B/74275c71e404f8e7fe1cae2f08e7a067764084b1.png) became minimal possible. In particular, it is allowed not to change order of elements at all.

## 输入格式

The first line contains two integers $ n,k $ ( $ 2<=n<=3·10^{5} $ , $ 1<=k<=min(5000,n-1) $ ).

The second line contains $ n $ integers $ A[1],A[2],...,A[n] $ ( $ -10^{9}<=A[i]<=10^{9} $ ), separate by spaces — elements of the array $ A $ .

## 输出格式

Print the minimum possible value of the sum described in the statement.

## 说明/提示

In the first test one of the optimal permutations is $ 1 4 2 $ .

In the second test the initial order is optimal.

In the third test one of the optimal permutations is $ 2 3 4 4 3 5 $ .

## 样例 #1

### 输入

```
3 2
1 2 4

```

### 输出

```
1

```

## 样例 #2

### 输入

```
5 2
3 -5 3 -5 3

```

### 输出

```
0

```

## 样例 #3

### 输入

```
6 3
4 3 4 3 2 5

```

### 输出

```
3

```

