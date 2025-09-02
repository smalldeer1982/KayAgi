---
title: "Squats"
layout: "post"
diff: 普及-
pid: CF424A
tag: []
---

# Squats

## 题目描述

Pasha has many hamsters and he makes them work out. Today, $ n $ hamsters ( $ n $ is even) came to work out. The hamsters lined up and each hamster either sat down or stood up.

For another exercise, Pasha needs exactly ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF424A/666f6519688863e0a36337875170dd12050e1c31.png) hamsters to stand up and the other hamsters to sit down. In one minute, Pasha can make some hamster ether sit down or stand up. How many minutes will he need to get what he wants if he acts optimally well?

## 输入格式

The first line contains integer $ n $ ( $ 2<=n<=200 $ ; $ n $ is even). The next line contains $ n $ characters without spaces. These characters describe the hamsters' position: the $ i $ -th character equals 'X', if the $ i $ -th hamster in the row is standing, and 'x', if he is sitting.

## 输出格式

In the first line, print a single integer — the minimum required number of minutes. In the second line, print a string that describes the hamsters' position after Pasha makes the required changes. If there are multiple optimal positions, print any of them.

## 样例 #1

### 输入

```
4
xxXx

```

### 输出

```
1
XxXx

```

## 样例 #2

### 输入

```
2
XX

```

### 输出

```
1
xX

```

## 样例 #3

### 输入

```
6
xXXxXx

```

### 输出

```
0
xXXxXx

```

