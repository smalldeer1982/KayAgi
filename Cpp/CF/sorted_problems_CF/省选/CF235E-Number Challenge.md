---
title: "Number Challenge"
layout: "post"
diff: 省选/NOI-
pid: CF235E
tag: ['数学', '枚举', '概率论']
---

# Number Challenge

## 题目描述

Let's denote $ d(n) $ as the number of divisors of a positive integer $ n $ . You are given three integers $ a $ , $ b $ and $ c $ . Your task is to calculate the following sum:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF235E/6b4d9893ce96bd0459ff1289a8bf3491052ac12a.png)Find the sum modulo $ 1073741824 $ $ (2^{30}) $ .

## 输入格式

The first line contains three space-separated integers $ a $ , $ b $ and $ c $ ( $ 1<=a,b,c<=2000 $ ).

## 输出格式

Print a single integer — the required sum modulo $ 1073741824 $ $ (2^{30}) $ .

## 说明/提示

For the first example.

- $ d(1·1·1)=d(1)=1 $ ;
- $ d(1·1·2)=d(2)=2 $ ;
- $ d(1·2·1)=d(2)=2 $ ;
- $ d(1·2·2)=d(4)=3 $ ;
- $ d(2·1·1)=d(2)=2 $ ;
- $ d(2·1·2)=d(4)=3 $ ;
- $ d(2·2·1)=d(4)=3 $ ;
- $ d(2·2·2)=d(8)=4 $ .

So the result is $ 1+2+2+3+2+3+3+4=20 $ .

## 样例 #1

### 输入

```
2 2 2

```

### 输出

```
20

```

## 样例 #2

### 输入

```
4 4 4

```

### 输出

```
328

```

## 样例 #3

### 输入

```
10 10 10

```

### 输出

```
11536

```

