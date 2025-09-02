---
title: "The Eternal Immortality"
layout: "post"
diff: 普及-
pid: CF869B
tag: []
---

# The Eternal Immortality

## 题目描述

Even if the world is full of counterfeits, I still regard it as wonderful.

Pile up herbs and incense, and arise again from the flames and ashes of its predecessor — as is known to many, the phoenix does it like this.

The phoenix has a rather long lifespan, and reincarnates itself once every $ a! $ years. Here $ a! $ denotes the factorial of integer $ a $ , that is, $ a!=1×2×...×a $ . Specifically, $ 0!=1 $ .

Koyomi doesn't care much about this, but before he gets into another mess with oddities, he is interested in the number of times the phoenix will reincarnate in a timespan of $ b! $ years, that is, ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF869B/e1b2fb98f4ea484515a807ebc0e143dd3b54b9f1.png). Note that when $ b>=a $ this value is always integer.

As the answer can be quite large, it would be enough for Koyomi just to know the last digit of the answer in decimal representation. And you're here to provide Koyomi with this knowledge.

## 输入格式

The first and only line of input contains two space-separated integers $ a $ and $ b $ ( $ 0<=a<=b<=10^{18} $ ).

## 输出格式

Output one line containing a single decimal digit — the last digit of the value that interests Koyomi.

## 说明/提示

In the first example, the last digit of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF869B/710c390d7d95fd1e439facb57a8db32614f140ba.png) is $ 2 $ ;

In the second example, the last digit of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF869B/9a0a3742a40de8b41b9545899252cb65c16a80ca.png) is $ 0 $ ;

In the third example, the last digit of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF869B/ba5fe125aa2ce1485bb9c22050da0a9acf975415.png) is $ 2 $ .

## 样例 #1

### 输入

```
2 4

```

### 输出

```
2

```

## 样例 #2

### 输入

```
0 10

```

### 输出

```
0

```

## 样例 #3

### 输入

```
107 109

```

### 输出

```
2

```

