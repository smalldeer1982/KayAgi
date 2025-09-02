---
title: "Exam"
layout: "post"
diff: 普及-
pid: CF534A
tag: []
---

# Exam

## 题目描述

An exam for $ n $ students will take place in a long and narrow room, so the students will sit in a line in some order. The teacher suspects that students with adjacent numbers ( $ i $ and $ i+1 $ ) always studied side by side and became friends and if they take an exam sitting next to each other, they will help each other for sure.

Your task is to choose the maximum number of students and make such an arrangement of students in the room that no two students with adjacent numbers sit side by side.

## 输入格式

A single line contains integer $ n $ ( $ 1<=n<=5000 $ ) — the number of students at an exam.

## 输出格式

In the first line print integer $ k $ — the maximum number of students who can be seated so that no two students with adjacent numbers sit next to each other.

In the second line print $ k $ distinct integers $ a_{1},a_{2},...,a_{k} $ ( $ 1<=a_{i}<=n $ ), where $ a_{i} $ is the number of the student on the $ i $ -th position. The students on adjacent positions mustn't have adjacent numbers. Formally, the following should be true: $ |a_{i}-a_{i+1}|≠1 $ for all $ i $ from $ 1 $ to $ k-1 $ .

If there are several possible answers, output any of them.

## 样例 #1

### 输入

```
6
```

### 输出

```
6
1 5 3 6 2 4
```

## 样例 #2

### 输入

```
3

```

### 输出

```
2
1 3
```

