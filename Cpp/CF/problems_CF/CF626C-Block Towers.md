---
title: "Block Towers"
layout: "post"
diff: 普及-
pid: CF626C
tag: ['枚举']
---

# Block Towers

## 题目描述

Students in a class are making towers of blocks. Each student makes a (non-zero) tower by stacking pieces lengthwise on top of each other. $ n $ of the students use pieces made of two blocks and $ m $ of the students use pieces made of three blocks.

The students don’t want to use too many blocks, but they also want to be unique, so no two students’ towers may contain the same number of blocks. Find the minimum height necessary for the tallest of the students' towers.

## 输入格式

The first line of the input contains two space-separated integers $ n $ and $ m $ ( $ 0<=n,m<=1000000 $ , $ n+m&gt;0 $ ) — the number of students using two-block pieces and the number of students using three-block pieces, respectively.

## 输出格式

Print a single integer, denoting the minimum possible height of the tallest tower.

## 说明/提示

In the first case, the student using two-block pieces can make a tower of height $ 4 $ , and the students using three-block pieces can make towers of height $ 3 $ , $ 6 $ , and $ 9 $ blocks. The tallest tower has a height of $ 9 $ blocks.

In the second case, the students can make towers of heights $ 2 $ , $ 4 $ , and $ 8 $ with two-block pieces and towers of heights $ 3 $ and $ 6 $ with three-block pieces, for a maximum height of $ 8 $ blocks.

## 样例 #1

### 输入

```
1 3

```

### 输出

```
9

```

## 样例 #2

### 输入

```
3 2

```

### 输出

```
8

```

## 样例 #3

### 输入

```
5 0

```

### 输出

```
10

```

