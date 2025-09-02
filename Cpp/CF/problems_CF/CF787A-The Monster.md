---
title: "The Monster"
layout: "post"
diff: 普及/提高-
pid: CF787A
tag: ['模拟', '排序', '中国剩余定理 CRT']
---

# The Monster

## 题目描述

A monster is chasing after Rick and Morty on another planet. They're so frightened that sometimes they scream. More accurately, Rick screams at times $ b,b+a,b+2a,b+3a,... $ and Morty screams at times $ d,d+c,d+2c,d+3c,... $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF787A/23c11249630f1c4252ef0b9cda8ec1bf9b317b5a.png)The Monster will catch them if at any point they scream at the same time, so it wants to know when it will catch them (the first time they scream at the same time) or that they will never scream at the same time.

## 输入格式

The first line of input contains two integers $ a $ and $ b $ ( $ 1<=a,b<=100 $ ).

The second line contains two integers $ c $ and $ d $ ( $ 1<=c,d<=100 $ ).

## 输出格式

Print the first time Rick and Morty will scream at the same time, or $ -1 $ if they will never scream at the same time.

## 说明/提示

In the first sample testcase, Rick's $ 5 $ th scream and Morty's $ 8 $ th time are at time $ 82 $ .

In the second sample testcase, all Rick's screams will be at odd times and Morty's will be at even times, so they will never scream at the same time.

## 样例 #1

### 输入

```
20 2
9 19

```

### 输出

```
82

```

## 样例 #2

### 输入

```
2 1
16 12

```

### 输出

```
-1

```

