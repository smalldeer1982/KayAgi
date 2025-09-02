---
title: "Forming Teams"
layout: "post"
diff: 提高+/省选-
pid: CF216B
tag: []
---

# Forming Teams

## 题目描述

One day $ n $ students come to the stadium. They want to play football, and for that they need to split into teams, the teams must have an equal number of people.

We know that this group of people has archenemies. Each student has at most two archenemies. Besides, if student $ A $ is an archenemy to student $ B $ , then student $ B $ is an archenemy to student $ A $ .

The students want to split so as no two archenemies were in one team. If splitting in the required manner is impossible, some students will have to sit on the bench.

Determine the minimum number of students you will have to send to the bench in order to form the two teams in the described manner and begin the game at last.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 2<=n<=100 $ , $ 1<=m<=100 $ ) — the number of students and the number of pairs of archenemies correspondingly.

Next $ m $ lines describe enmity between students. Each enmity is described as two numbers $ a_{i} $ and $ b_{i} $ ( $ 1<=a_{i},b_{i}<=n $ , $ a_{i}≠b_{i} $ ) — the indexes of the students who are enemies to each other. Each enmity occurs in the list exactly once. It is guaranteed that each student has no more than two archenemies.

You can consider the students indexed in some manner with distinct integers from 1 to $ n $ .

## 输出格式

Print a single integer — the minimum number of students you will have to send to the bench in order to start the game.

## 样例 #1

### 输入

```
5 4
1 2
2 4
5 3
1 4

```

### 输出

```
1
```

## 样例 #2

### 输入

```
6 2
1 4
3 4

```

### 输出

```
0
```

## 样例 #3

### 输入

```
6 6
1 2
2 3
3 1
4 5
5 6
6 4

```

### 输出

```
2
```

