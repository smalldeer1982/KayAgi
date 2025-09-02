---
title: "Ciel and Robot"
layout: "post"
diff: 普及+/提高
pid: CF321A
tag: []
---

# Ciel and Robot

## 题目描述

Fox Ciel has a robot on a 2D plane. Initially it is located in (0, 0). Fox Ciel code a command to it. The command was represented by string $ s $ . Each character of $ s $ is one move operation. There are four move operations at all:

- 'U': go up, (x, y) $ → $ (x, y+1);
- 'D': go down, (x, y) $ → $ (x, y-1);
- 'L': go left, (x, y) $ → $ (x-1, y);
- 'R': go right, (x, y) $ → $ (x+1, y).

The robot will do the operations in $ s $ from left to right, and repeat it infinite times. Help Fox Ciel to determine if after some steps the robot will located in $ (a,b) $ .

## 输入格式

The first line contains two integers $ a $ and $ b $ , ( $ -10^{9}<=a,b<=10^{9} $ ). The second line contains a string $ s $ ( $ 1<=|s|<=100 $ , $ s $ only contains characters 'U', 'D', 'L', 'R') — the command.

## 输出格式

Print "Yes" if the robot will be located at $ (a,b) $ , and "No" otherwise.

## 说明/提示

In the first and second test case, command string is "RU", so the robot will go right, then go up, then right, and then up and so on.

The locations of its moves are (0, 0) $ → $ (1, 0) $ → $ (1, 1) $ → $ (2, 1) $ → $ (2, 2) $ → $ $ ... $

So it can reach (2, 2) but not (1, 2).

## 样例 #1

### 输入

```
2 2
RU

```

### 输出

```
Yes

```

## 样例 #2

### 输入

```
1 2
RU

```

### 输出

```
No

```

## 样例 #3

### 输入

```
-1 1000000000
LRRLU

```

### 输出

```
Yes

```

## 样例 #4

### 输入

```
0 0
D

```

### 输出

```
Yes

```

