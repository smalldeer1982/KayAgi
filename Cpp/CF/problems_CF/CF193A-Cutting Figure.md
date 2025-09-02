---
title: "Cutting Figure"
layout: "post"
diff: 普及/提高-
pid: CF193A
tag: []
---

# Cutting Figure

## 题目描述

You've gotten an $ n×m $ sheet of squared paper. Some of its squares are painted. Let's mark the set of all painted squares as $ A $ . Set $ A $ is connected. Your task is to find the minimum number of squares that we can delete from set $ A $ to make it not connected.

A set of painted squares is called connected, if for every two squares $ a $ and $ b $ from this set there is a sequence of squares from the set, beginning in $ a $ and ending in $ b $ , such that in this sequence any square, except for the last one, shares a common side with the square that follows next in the sequence. An empty set and a set consisting of exactly one square are connected by definition.

## 输入格式

The first input line contains two space-separated integers $ n $ and $ m $ ( $ 1<=n,m<=50 $ ) — the sizes of the sheet of paper.

Each of the next $ n $ lines contains $ m $ characters — the description of the sheet of paper: the $ j $ -th character of the $ i $ -th line equals either "#", if the corresponding square is painted (belongs to set $ A $ ), or equals "." if the corresponding square is not painted (does not belong to set $ A $ ). It is guaranteed that the set of all painted squares $ A $ is connected and isn't empty.

## 输出格式

On the first line print the minimum number of squares that need to be deleted to make set $ A $ not connected. If it is impossible, print -1.

## 说明/提示

In the first sample you can delete any two squares that do not share a side. After that the set of painted squares is not connected anymore.

The note to the second sample is shown on the figure below. To the left there is a picture of the initial set of squares. To the right there is a set with deleted squares. The deleted squares are marked with crosses.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF193A/cc2de3ad5afd093ec1251f928cbdde2a451e56d2.png)

## 样例 #1

### 输入

```
5 4
####
#..#
#..#
#..#
####

```

### 输出

```
2

```

## 样例 #2

### 输入

```
5 5
#####
#...#
#####
#...#
#####

```

### 输出

```
2

```

