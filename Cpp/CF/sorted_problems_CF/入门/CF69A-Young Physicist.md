---
title: "Young Physicist"
layout: "post"
diff: 入门
pid: CF69A
tag: []
---

# Young Physicist

## 题目描述

A guy named Vasya attends the final grade of a high school. One day Vasya decided to watch a match of his favorite hockey team. And, as the boy loves hockey very much, even more than physics, he forgot to do the homework. Specifically, he forgot to complete his physics tasks. Next day the teacher got very angry at Vasya and decided to teach him a lesson. He gave the lazy student a seemingly easy task: You are given an idle body in space and the forces that affect it. The body can be considered as a material point with coordinates (0; 0; 0). Vasya had only to answer whether it is in equilibrium. "Piece of cake" — thought Vasya, we need only to check if the sum of all vectors is equal to 0. So, Vasya began to solve the problem. But later it turned out that there can be lots and lots of these forces, and Vasya can not cope without your help. Help him. Write a program that determines whether a body is idle or is moving by the given vectors of forces.

## 输入格式

The first line contains a positive integer $ n $ ( $ 1<=n<=100 $ ), then follow $ n $ lines containing three integers each: the $ x_{i} $ coordinate, the $ y_{i} $ coordinate and the $ z_{i} $ coordinate of the force vector, applied to the body ( $ -100<=x_{i},y_{i},z_{i}<=100 $ ).

## 输出格式

Print the word "YES" if the body is in equilibrium, or the word "NO" if it is not.

## 样例 #1

### 输入

```
3
4 1 7
-2 4 -1
1 -5 -3

```

### 输出

```
NO
```

## 样例 #2

### 输入

```
3
3 -1 7
-5 2 -4
2 -1 -3

```

### 输出

```
YES
```

