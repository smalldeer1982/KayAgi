---
title: "Contest"
layout: "post"
diff: 普及/提高-
pid: CF501A
tag: []
---

# Contest

## 题目描述

Misha and Vasya participated in a Codeforces contest. Unfortunately, each of them solved only one problem, though successfully submitted it at the first attempt. Misha solved the problem that costs $ a $ points and Vasya solved the problem that costs $ b $ points. Besides, Misha submitted the problem $ c $ minutes after the contest started and Vasya submitted the problem $ d $ minutes after the contest started. As you know, on Codeforces the cost of a problem reduces as a round continues. That is, if you submit a problem that costs $ p $ points $ t $ minutes after the contest started, you get ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF501A/0c1954e97a47d9a6cd1567e3d0ad4f4a76ada737.png) points.

Misha and Vasya are having an argument trying to find out who got more points. Help them to find out the truth.

## 输入格式

The first line contains four integers $ a $ , $ b $ , $ c $ , $ d $ ( $ 250<=a,b<=3500 $ , $ 0<=c,d<=180 $ ).

It is guaranteed that numbers $ a $ and $ b $ are divisible by $ 250 $ (just like on any real Codeforces round).

## 输出格式

Output on a single line:

"Misha" (without the quotes), if Misha got more points than Vasya.

"Vasya" (without the quotes), if Vasya got more points than Misha.

"Tie" (without the quotes), if both of them got the same number of points.

## 样例 #1

### 输入

```
500 1000 20 30

```

### 输出

```
Vasya

```

## 样例 #2

### 输入

```
1000 1000 1 1

```

### 输出

```
Tie

```

## 样例 #3

### 输入

```
1500 1000 176 177

```

### 输出

```
Misha

```

