---
title: "SPIRALGR - A Famous Grid"
layout: "post"
diff: 难度0
pid: SP11582
tag: []
---

# SPIRALGR - A Famous Grid

## 题目描述

Mr. B has recently discovered the grid named "spiral grid". Construct the grid like the following figure. (The grid is actually infinite. The figure is only a small part of it.)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/SP11582/5c187a8f21f1c66e1a3f7e18b0a4d570bb2602ae.png)

Considering traveling around it, you are free to any cell containing a composite number or 1, but traveling to any cell containing a prime number is disallowed. You can travel up, down, left or right, but not diagonally. Write a program to find the length of the shortest path between pairs of nonprime numbers, or report it's impossible.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/SP11582/bd4b63e262994181fbe0fca5cb1ea40f1a881d2f.png)

## 输入格式

Each test case is described by a line of input containing two nonprime integer 1 <=**x**, **y**<=10,000.

## 输出格式

For each test case display its case number followed by the length of the shortest path or **impossible** in one line.

## 样例 #1

### 输入

```
1 4
9 32
10 12
```

### 输出

```
Case 1: 1
Case 2: 7
Case 3: impossible
```

