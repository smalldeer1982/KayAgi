---
title: "Beautiful Pairs of Numbers"
layout: "post"
diff: 省选/NOI-
pid: CF403D
tag: []
---

# Beautiful Pairs of Numbers

## 题目描述

The sequence of integer pairs $ (a_{1},b_{1}),(a_{2},b_{2}),...,(a_{k},b_{k}) $ is beautiful, if the following statements are fulfilled:

- $ 1<=a_{1}<=b_{1}&lt;a_{2}<=b_{2}&lt;...&lt;a_{k}<=b_{k}<=n $ , where $ n $ is a given positive integer;
- all numbers $ b_{1}-a_{1} $ , $ b_{2}-a_{2} $ , $ ... $ , $ b_{k}-a_{k} $ are distinct.

For the given number $ n $ find the number of beautiful sequences of length $ k $ . As the answer can be rather large, print the remainder after dividing it by $ 1000000007 $ $ (10^{9}+7) $ .

## 输入格式

The first line contains integer $ t $ ( $ 1<=t<=2·10^{5} $ ) — the number of the test data.

Each of the next $ t $ lines contains two integers $ n $ and $ k $ ( $ 1<=k<=n<=1000 $ ).

## 输出格式

For each test from the input print the answer to the problem modulo $ 1000000007 $ $ (10^{9}+7) $ . Print the answers to the tests in the order in which the tests are given in the input.

## 说明/提示

In the first test sample there is exactly one beautiful sequence: $ (1,1) $ .

In the second test sample, the following sequences are beautiful:

- $ (1,1) $ ;
- $ (1,2) $ ;
- $ (2,2) $ .

In the fourth test sample, the following sequences are beautiful:

- $ (1,1) $ ;
- $ (1,2) $ ;
- $ (1,3) $ ;
- $ (2,2) $ ;
- $ (2,3) $ ;
- $ (3,3) $ .

In the fifth test sample, the following sequences are beautiful:

- $ (1,1),(2,3) $ ;
- $ (1,2),(3,3) $ .

In the third and sixth samples, there are no beautiful sequences.

## 样例 #1

### 输入

```
6
1 1
2 1
2 2
3 1
3 2
3 3

```

### 输出

```
1
3
0
6
2
0

```

