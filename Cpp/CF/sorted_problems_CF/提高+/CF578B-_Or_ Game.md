---
title: ""Or" Game"
layout: "post"
diff: 提高+/省选-
pid: CF578B
tag: []
---

# "Or" Game

## 题目描述

You are given $ n $ numbers $ a_{1},a_{2},...,a_{n} $ . You can perform at most $ k $ operations. For each operation you can multiply one of the numbers by $ x $ . We want to make ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF578B/4957ea745191dedda7c88dd7a9c0749def3ef4fd.png) as large as possible, where ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF578B/228ea8924d84782194ed9458038dbd5525d21a6e.png) denotes the bitwise OR.

Find the maximum possible value of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF578B/4957ea745191dedda7c88dd7a9c0749def3ef4fd.png) after performing at most $ k $ operations optimally.

## 输入格式

The first line contains three integers $ n $ , $ k $ and $ x $ ( $ 1<=n<=200000 $ , $ 1<=k<=10 $ , $ 2<=x<=8 $ ).

The second line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ ( $ 0<=a_{i}<=10^{9} $ ).

## 输出格式

Output the maximum value of a bitwise OR of sequence elements after performing operations.

## 说明/提示

For the first sample, any possible choice of doing one operation will result the same three numbers $ 1 $ , $ 1 $ , $ 2 $ so the result is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF578B/aa4bd67912899e33d42fc5cdc56c32c5fb40c4e1.png).

For the second sample if we multiply $ 8 $ by $ 3 $ two times we'll get $ 72 $ . In this case the numbers will become $ 1 $ , $ 2 $ , $ 4 $ , $ 72 $ so the OR value will be $ 79 $ and is the largest possible result.

## 样例 #1

### 输入

```
3 1 2
1 1 1

```

### 输出

```
3

```

## 样例 #2

### 输入

```
4 2 3
1 2 4 8

```

### 输出

```
79

```

