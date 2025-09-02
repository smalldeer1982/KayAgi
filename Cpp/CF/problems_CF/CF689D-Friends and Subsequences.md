---
title: "Friends and Subsequences"
layout: "post"
diff: 普及+/提高
pid: CF689D
tag: []
---

# Friends and Subsequences

## 题目描述

Mike and !Mike are old childhood rivals, they are opposite in everything they do, except programming. Today they have a problem they cannot solve on their own, but together (with you) — who knows?

Every one of them has an integer sequences $ a $ and $ b $ of length $ n $ . Being given a query of the form of pair of integers $ (l,r) $ , Mike can instantly tell the value of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF689D/77a91e450d8c58a8cff349889db0f7900b8e3ace.png) while !Mike can instantly tell the value of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF689D/7594cca965e5cc163cc16e32e5bed1c0ba0fa037.png).

Now suppose a robot (you!) asks them all possible different queries of pairs of integers $ (l,r) $ $ (1<=l<=r<=n) $ (so he will make exactly $ n(n+1)/2 $ queries) and counts how many times their answers coincide, thus for how many pairs ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF689D/72e28ce968021e0cd2b5fe1a6f144994e8f8338b.png) is satisfied.

How many occasions will the robot count?

## 输入格式

The first line contains only integer $ n $ ( $ 1<=n<=200000 $ ).

The second line contains $ n $ integer numbers $ a_{1},a_{2},...,a_{n} $ ( $ -10^{9}<=a_{i}<=10^{9} $ ) — the sequence $ a $ .

The third line contains $ n $ integer numbers $ b_{1},b_{2},...,b_{n} $ ( $ -10^{9}<=b_{i}<=10^{9} $ ) — the sequence $ b $ .

## 输出格式

Print the only integer number — the number of occasions the robot will count, thus for how many pairs ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF689D/72e28ce968021e0cd2b5fe1a6f144994e8f8338b.png) is satisfied.

## 说明/提示

The occasions in the first sample case are:

1\. $ l=4 $ , $ r=4 $ since $ max{2}=min{2} $ .

2\. $ l=4 $ , $ r=5 $ since $ max{2,1}=min{2,3} $ .

There are no occasions in the second sample case since Mike will answer $ 3 $ to any query pair, but !Mike will always answer $ 1 $ .

## 样例 #1

### 输入

```
6
1 2 3 2 1 4
6 7 1 2 3 2

```

### 输出

```
2

```

## 样例 #2

### 输入

```
3
3 3 3
1 1 1

```

### 输出

```
0

```

