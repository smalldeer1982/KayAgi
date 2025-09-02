---
title: "Solution for Cube"
layout: "post"
diff: 普及/提高-
pid: CF887C
tag: []
---

# Solution for Cube

## 题目描述

During the breaks between competitions, top-model Izabella tries to develop herself and not to be bored. For example, now she tries to solve Rubik's cube 2x2x2.

It's too hard to learn to solve Rubik's cube instantly, so she learns to understand if it's possible to solve the cube in some state using 90-degrees rotation of one face of the cube in any direction.

To check her answers she wants to use a program which will for some state of cube tell if it's possible to solve it using one rotation, described above.

Cube is called solved if for each face of cube all squares on it has the same color.

<a>https://en.wikipedia.org/wiki/Rubik's\_Cube</a>

## 输入格式

In first line given a sequence of 24 integers $ a_{i} $ ( $ 1<=a_{i}<=6 $ ), where $ a_{i} $ denotes color of $ i $ -th square. There are exactly 4 occurrences of all colors in this sequence.

## 输出格式

Print «YES» (without quotes) if it's possible to solve cube using one rotation and «NO» (without quotes) otherwise.

## 说明/提示

In first test case cube looks like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF887C/73004469d714c2206d92e2fac016d4fc092e2426.png)In second test case cube looks like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF887C/37b512d2c715516faa04a8cfe0023b26918d7893.png)It's possible to solve cube by rotating face with squares with numbers 13, 14, 15, 16.

## 样例 #1

### 输入

```
2 5 4 6 1 3 6 2 5 5 1 2 3 5 3 1 1 2 4 6 6 4 3 4

```

### 输出

```
NO
```

## 样例 #2

### 输入

```
5 3 5 3 2 5 2 5 6 2 6 2 4 4 4 4 1 1 1 1 6 3 6 3

```

### 输出

```
YES
```

