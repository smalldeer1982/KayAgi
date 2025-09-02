---
title: "Degenerate Matrix"
layout: "post"
diff: 提高+/省选-
pid: CF549H
tag: []
---

# Degenerate Matrix

## 题目描述

The determinant of a matrix $ 2×2 $ is defined as follows:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF549H/703e7742f6308e45304e4cbb5699ead68258b334.png)A matrix is called degenerate if its determinant is equal to zero.

The norm $ ||A|| $ of a matrix $ A $ is defined as a maximum of absolute values of its elements.

You are given a matrix ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF549H/a81c8b5329fb3da53e1141c4dfaddc43c5a88073.png). Consider any degenerate matrix $ B $ such that norm $ ||A-B|| $ is minimum possible. Determine $ ||A-B|| $ .

## 输入格式

The first line contains two integers $ a $ and $ b $ ( $ |a|,|b|<=10^{9} $ ), the elements of the first row of matrix $ A $ .

The second line contains two integers $ c $ and $ d $ ( $ |c|,|d|<=10^{9} $ ) the elements of the second row of matrix $ A $ .

## 输出格式

Output a single real number, the minimum possible value of $ ||A-B|| $ . Your answer is considered to be correct if its absolute or relative error does not exceed $ 10^{-9} $ .

## 说明/提示

In the first sample matrix $ B $ is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF549H/d2b53d754fc99e5b9d2dd8345dc06167db4fa5e6.png)

In the second sample matrix $ B $ is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF549H/62b29d043f4b99bb231bfdf3cac3fe3c6d0ab461.png)

## 样例 #1

### 输入

```
1 2
3 4

```

### 输出

```
0.2000000000

```

## 样例 #2

### 输入

```
1 0
0 1

```

### 输出

```
0.5000000000

```

