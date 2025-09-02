---
title: "Magnets"
layout: "post"
diff: 入门
pid: CF344A
tag: ['模拟', '概率论']
---

# Magnets

## 题目描述

Mad scientist Mike entertains himself by arranging rows of dominoes. He doesn't need dominoes, though: he uses rectangular magnets instead. Each magnet has two poles, positive (a "plus") and negative (a "minus"). If two magnets are put together at a close distance, then the like poles will repel each other and the opposite poles will attract each other.

Mike starts by laying one magnet horizontally on the table. During each following step Mike adds one more magnet horizontally to the right end of the row. Depending on how Mike puts the magnet on the table, it is either attracted to the previous one (forming a group of multiple magnets linked together) or repelled by it (then Mike lays this magnet at some distance to the right from the previous one). We assume that a sole magnet not linked to others forms a group of its own.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF344A/5ad7b55de90b4c95ae686ce6e02cbb9c5dff4d4e.png)Mike arranged multiple magnets in a row. Determine the number of groups that the magnets formed.

## 输入格式

The first line of the input contains an integer $ n $ ( $ 1<=n<=100000 $ ) — the number of magnets. Then $ n $ lines follow. The $ i $ -th line ( $ 1<=i<=n $ ) contains either characters "01", if Mike put the $ i $ -th magnet in the "plus-minus" position, or characters "10", if Mike put the magnet in the "minus-plus" position.

## 输出格式

On the single line of the output print the number of groups of magnets.

## 说明/提示

The first testcase corresponds to the figure. The testcase has three groups consisting of three, one and two magnets.

The second testcase has two groups, each consisting of two magnets.

## 样例 #1

### 输入

```
6
10
10
10
01
10
10

```

### 输出

```
3

```

## 样例 #2

### 输入

```
4
01
01
10
10

```

### 输出

```
2

```

