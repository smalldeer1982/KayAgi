---
title: "George and Accommodation"
layout: "post"
diff: 入门
pid: CF467A
tag: []
---

# George and Accommodation

## 题目描述

George has recently entered the BSUCP (Berland State University for Cool Programmers). George has a friend Alex who has also entered the university. Now they are moving into a dormitory.

George and Alex want to live in the same room. The dormitory has $ n $ rooms in total. At the moment the $ i $ -th room has $ p_{i} $ people living in it and the room can accommodate $ q_{i} $ people in total ( $ p_{i}<=q_{i} $ ). Your task is to count how many rooms has free place for both George and Alex.

## 输入格式

The first line contains a single integer $ n $ $ (1<=n<=100) $ — the number of rooms.

The $ i $ -th of the next $ n $ lines contains two integers $ p_{i} $ and $ q_{i} $ $ (0<=p_{i}<=q_{i}<=100) $ — the number of people who already live in the $ i $ -th room and the room's capacity.

## 输出格式

Print a single integer — the number of rooms where George and Alex can move in.

## 样例 #1

### 输入

```
3
1 1
2 2
3 3

```

### 输出

```
0

```

## 样例 #2

### 输入

```
3
1 10
0 10
10 10

```

### 输出

```
2

```

