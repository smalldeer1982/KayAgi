---
title: "Guess Your Way Out!"
layout: "post"
diff: 普及+/提高
pid: CF507C
tag: []
---

# Guess Your Way Out!

## 题目描述

Amr bought a new video game "Guess Your Way Out!". The goal of the game is to find an exit from the maze that looks like a perfect binary tree of height $ h $ . The player is initially standing at the root of the tree and the exit from the tree is located at some leaf node.

Let's index all the leaf nodes from the left to the right from 1 to $ 2^{h} $ . The exit is located at some node $ n $ where $ 1<=n<=2^{h} $ , the player doesn't know where the exit is so he has to guess his way out!

Amr follows simple algorithm to choose the path. Let's consider infinite command string "LRLRLRLRL..." (consisting of alternating characters 'L' and 'R'). Amr sequentially executes the characters of the string using following rules:

- Character 'L' means "go to the left child of the current node";
- Character 'R' means "go to the right child of the current node";
- If the destination node is already visited, Amr skips current command, otherwise he moves to the destination node;
- If Amr skipped two consecutive commands, he goes back to the parent of the current node before executing next command;
- If he reached a leaf node that is not the exit, he returns to the parent of the current node;
- If he reaches an exit, the game is finished.

Now Amr wonders, if he follows this algorithm, how many nodes he is going to visit before reaching the exit?

## 输入格式

Input consists of two integers $ h,n $ ( $ 1<=h<=50 $ , $ 1<=n<=2^{h} $ ).

## 输出格式

Output a single integer representing the number of nodes (excluding the exit node) Amr is going to visit before reaching the exit by following this algorithm.

## 说明/提示

A perfect binary tree of height $ h $ is a binary tree consisting of $ h+1 $ levels. Level $ 0 $ consists of a single node called root, level $ h $ consists of $ 2^{h} $ nodes called leaves. Each node that is not a leaf has exactly two children, left and right one.

Following picture illustrates the sample test number $ 3 $ . Nodes are labeled according to the order of visit.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF507C/1071268d93324fbfe90557eb5569861c59d6d7a2.png)

## 样例 #1

### 输入

```
1 2

```

### 输出

```
2
```

## 样例 #2

### 输入

```
2 3

```

### 输出

```
5
```

## 样例 #3

### 输入

```
3 6

```

### 输出

```
10
```

## 样例 #4

### 输入

```
10 1024

```

### 输出

```
2046
```

