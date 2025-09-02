---
title: "REQ"
layout: "post"
diff: 省选/NOI-
pid: CF594D
tag: []
---

# REQ

## 题目描述

Today on a math lesson the teacher told Vovochka that the Euler function of a positive integer $ φ(n) $ is an arithmetic function that counts the positive integers less than or equal to n that are relatively prime to n. The number $ 1 $ is coprime to all the positive integers and $ φ(1)=1 $ .

Now the teacher gave Vovochka an array of $ n $ positive integers $ a_{1},a_{2},...,a_{n} $ and a task to process $ q $ queries $ l_{i} $ $ r_{i} $ — to calculate and print ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF594D/1bd06985c605f4dcc1229ea18fcf81458cbdb3b0.png) modulo $ 10^{9}+7 $ . As it is too hard for a second grade school student, you've decided to help Vovochka.

## 输入格式

The first line of the input contains number $ n $ ( $ 1<=n<=200000 $ ) — the length of the array given to Vovochka. The second line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=10^{6} $ ).

The third line contains integer $ q $ ( $ 1<=q<=200000 $ ) — the number of queries. Next $ q $ lines contain the queries, one per line. Each query is defined by the boundaries of the segment $ l_{i} $ and $ r_{i} $ ( $ 1<=l_{i}<=r_{i}<=n $ ).

## 输出格式

Print $ q $ numbers — the value of the Euler function for each query, calculated modulo $ 10^{9}+7 $ .

## 说明/提示

In the second sample the values are calculated like that:

- $ φ(13·52·6)=φ(4056)=1248 $
- $ φ(52·6·10·1)=φ(3120)=768 $
- $ φ(24·63·13·52·6·10·1)=φ(61326720)=12939264 $
- $ φ(63·13·52)=φ(42588)=11232 $
- $ φ(13·52·6·10)=φ(40560)=9984 $
- $ φ(63·13·52·6·10)=φ(2555280)=539136 $

## 样例 #1

### 输入

```
10
1 2 3 4 5 6 7 8 9 10
7
1 1
3 8
5 6
4 8
8 10
7 9
7 10

```

### 输出

```
1
4608
8
1536
192
144
1152

```

## 样例 #2

### 输入

```
7
24 63 13 52 6 10 1
6
3 5
4 7
1 7
2 4
3 6
2 6

```

### 输出

```
1248
768
12939264
11232
9984
539136

```

