---
title: "Counting-out Rhyme"
layout: "post"
diff: 普及-
pid: CF792B
tag: []
---

# Counting-out Rhyme

## 题目描述

 $ n $ children are standing in a circle and playing the counting-out game. Children are numbered clockwise from $ 1 $ to $ n $ . In the beginning, the first child is considered the leader. The game is played in $ k $ steps. In the $ i $ -th step the leader counts out $ a_{i} $ people in clockwise order, starting from the next person. The last one to be pointed at by the leader is eliminated, and the next player after him becomes the new leader.

For example, if there are children with numbers $ [8,10,13,14,16] $ currently in the circle, the leader is child $ 13 $ and $ a_{i}=12 $ , then counting-out rhyme ends on child $ 16 $ , who is eliminated. Child $ 8 $ becomes the leader.

You have to write a program which prints the number of the child to be eliminated on every step.

## 输入格式

The first line contains two integer numbers $ n $ and $ k $ ( $ 2<=n<=100 $ , $ 1<=k<=n-1 $ ).

The next line contains $ k $ integer numbers $ a_{1},a_{2},...,a_{k} $ ( $ 1<=a_{i}<=10^{9} $ ).

## 输出格式

Print $ k $ numbers, the $ i $ -th one corresponds to the number of child to be eliminated at the $ i $ -th step.

## 说明/提示

Let's consider first example:

- In the first step child $ 4 $ is eliminated, child $ 5 $ becomes the leader.
- In the second step child $ 2 $ is eliminated, child $ 3 $ becomes the leader.
- In the third step child $ 5 $ is eliminated, child $ 6 $ becomes the leader.
- In the fourth step child $ 6 $ is eliminated, child $ 7 $ becomes the leader.
- In the final step child $ 1 $ is eliminated, child $ 3 $ becomes the leader.

## 样例 #1

### 输入

```
7 5
10 4 11 4 1

```

### 输出

```
4 2 5 6 1 

```

## 样例 #2

### 输入

```
3 2
2 5

```

### 输出

```
3 2 

```

