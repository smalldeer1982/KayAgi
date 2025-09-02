---
title: "Permanent"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF468E
tag: []
---

# Permanent

## 题目描述

Little X has solved the #P-complete problem in polynomial time recently. So he gives this task to you.

There is a special $ n×n $ matrix $ A $ , you should calculate its permanent modulo $ 1000000007 (10^{9}+7) $ . The special property of matrix $ A $ is almost all its elements equal to $ 1 $ . Only $ k $ elements have specified value.

You can find the definition of permanent at the link: https://en.wikipedia.org/wiki/Permanent

## 输入格式

The first line contains two space-separated integers $ n,k $ ( $ 1<=n<=10^{5}; 1<=k<=50 $ ).

The next $ k $ lines contain the description of the matrix. The $ i $ -th line contains three space-separated integers $ x_{i},y_{i},w_{i} $ ( $ 1<=x_{i},y_{i}<=n; 0<=w_{i}<=10^{9} $ ). These numbers denote that $ A_{xi},y_{i}=w_{i} $ . All the elements of the matrix except of the given elements are equal to $ 1 $ .

It's guaranteed that all the positions $ (x_{i},y_{i}) $ are distinct.

## 输出格式

Print the permanent of the matrix modulo $ 1000000007 (10^{9}+7) $ .

## 样例 #1

### 输入

```
3 1
1 1 2

```

### 输出

```
8

```

## 样例 #2

### 输入

```
10 10
3 3 367056794
6 2 124561273
1 3 46718146
6 9 415916869
10 5 985968336
3 1 526792265
1 4 386357058
10 4 349304187
2 7 102032499
3 6 502679075

```

### 输出

```
233333333

```

