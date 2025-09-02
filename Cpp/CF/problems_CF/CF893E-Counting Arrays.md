---
title: "Counting Arrays"
layout: "post"
diff: 提高+/省选-
pid: CF893E
tag: []
---

# Counting Arrays

## 题目描述

You are given two positive integer numbers $ x $ and $ y $ . An array $ F $ is called an  $ y $ -factorization of $ x $ iff the following conditions are met:

- There are $ y $ elements in $ F $ , and all of them are integer numbers;
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF893E/d8d5a9dcea7fa6a7abfa89d7da34d6fb180c0f69.png).

You have to count the number of pairwise distinct arrays that are $ y $ -factorizations of $ x $ . Two arrays $ A $ and $ B $ are considered different iff there exists at least one index $ i $ ( $ 1<=i<=y $ ) such that $ A_{i}≠B_{i} $ . Since the answer can be very large, print it modulo $ 10^{9}+7 $ .

## 输入格式

The first line contains one integer $ q $ ( $ 1<=q<=10^{5} $ ) — the number of testcases to solve.

Then $ q $ lines follow, each containing two integers $ x_{i} $ and $ y_{i} $ ( $ 1<=x_{i},y_{i}<=10^{6} $ ). Each of these lines represents a testcase.

## 输出格式

Print $ q $ integers. $ i $ -th integer has to be equal to the number of $ y_{i} $ -factorizations of $ x_{i} $ modulo $ 10^{9}+7 $ .

## 说明/提示

In the second testcase of the example there are six $ y $ -factorizations:

- $ {-4,-1} $ ;
- $ {-2,-2} $ ;
- $ {-1,-4} $ ;
- $ {1,4} $ ;
- $ {2,2} $ ;
- $ {4,1} $ .

## 样例 #1

### 输入

```
2
6 3
4 2

```

### 输出

```
36
6

```

