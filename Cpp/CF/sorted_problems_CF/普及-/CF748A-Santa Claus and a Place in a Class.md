---
title: "Santa Claus and a Place in a Class"
layout: "post"
diff: 普及-
pid: CF748A
tag: []
---

# Santa Claus and a Place in a Class

## 题目描述

Santa Claus is the first who came to the Christmas Olympiad, and he is going to be the first to take his place at a desk! In the classroom there are $ n $ lanes of $ m $ desks each, and there are two working places at each of the desks. The lanes are numbered from $ 1 $ to $ n $ from the left to the right, the desks in a lane are numbered from $ 1 $ to $ m $ starting from the blackboard. Note that the lanes go perpendicularly to the blackboard, not along it (see picture).

The organizers numbered all the working places from $ 1 $ to $ 2nm $ . The places are numbered by lanes (i. e. all the places of the first lane go first, then all the places of the second lane, and so on), in a lane the places are numbered starting from the nearest to the blackboard (i. e. from the first desk in the lane), at each desk, the place on the left is numbered before the place on the right.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF748A/bbf8fc48769a6dddf0555cdcd0723e32248a57bd.png)The picture illustrates the first and the second samples.Santa Clause knows that his place has number $ k $ . Help him to determine at which lane at which desk he should sit, and whether his place is on the left or on the right!

## 输入格式

The only line contains three integers $ n $ , $ m $ and $ k $ ( $ 1<=n,m<=10000 $ , $ 1<=k<=2nm $ ) — the number of lanes, the number of desks in each lane and the number of Santa Claus' place.

## 输出格式

Print two integers: the number of lane $ r $ , the number of desk $ d $ , and a character $ s $ , which stands for the side of the desk Santa Claus. The character $ s $ should be "L", if Santa Clause should sit on the left, and "R" if his place is on the right.

## 说明/提示

The first and the second samples are shown on the picture. The green place corresponds to Santa Claus' place in the first example, the blue place corresponds to Santa Claus' place in the second example.

In the third sample there are two lanes with four desks in each, and Santa Claus has the fourth place. Thus, his place is in the first lane at the second desk on the right.

## 样例 #1

### 输入

```
4 3 9

```

### 输出

```
2 2 L

```

## 样例 #2

### 输入

```
4 3 24

```

### 输出

```
4 3 R

```

## 样例 #3

### 输入

```
2 4 4

```

### 输出

```
1 2 R

```

