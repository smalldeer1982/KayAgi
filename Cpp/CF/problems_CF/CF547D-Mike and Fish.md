---
title: "Mike and Fish"
layout: "post"
diff: 省选/NOI-
pid: CF547D
tag: ['图论', '欧拉回路', '二分图']
---

# Mike and Fish

## 题目描述

As everyone knows, bears love fish. But Mike is a strange bear; He hates fish! The even more strange thing about him is he has an infinite number of blue and red fish.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF547D/031dc6fdab66492c31079b30a48004c3918930a2.png)He has marked $ n $ distinct points in the plane. $ i $ -th point is point $ (x_{i},y_{i}) $ . He wants to put exactly one fish in each of these points such that the difference between the number of red fish and the blue fish on each horizontal or vertical line is at most 1.

He can't find a way to perform that! Please help him.

## 输入格式

The first line of input contains integer $ n $ ( $ 1<=n<=2×10^{5} $ ).

The next $ n $ lines contain the information about the points, $ i $ -th line contains two integers $ x_{i} $ and $ y_{i} $ ( $ 1<=x_{i},y_{i}<=2×10^{5} $ ), the $ i $ -th point coordinates.

It is guaranteed that there is at least one valid answer.

## 输出格式

Print the answer as a sequence of $ n $ characters 'r' (for red) or 'b' (for blue) where $ i $ -th character denotes the color of the fish in the $ i $ -th point.

## 样例 #1

### 输入

```
4
1 1
1 2
2 1
2 2

```

### 输出

```
brrb

```

## 样例 #2

### 输入

```
3
1 1
1 2
2 1

```

### 输出

```
brr

```

