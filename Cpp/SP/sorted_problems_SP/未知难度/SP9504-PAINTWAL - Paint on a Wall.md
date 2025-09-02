---
title: "PAINTWAL - Paint on a Wall"
layout: "post"
diff: 难度0
pid: SP9504
tag: []
---

# PAINTWAL - Paint on a Wall

## 题目描述

Annie wants to paint her wall to an expected pattern. The wall can be represented as a 2\***n** grid and each grid will be painted only one color. Annie has a brush which could paint a rectangular area of the wall at a single step. The paint could be overlap and the newly painted color will replace the older one.

For a given pattern of the wall, your task is to help Annie find out the minimum possible number of painting steps. You can assume that the wall remains unpainted until Annie paint some colors on it.

## 输入格式

There are multiple test cases in the input. The first line contains the number of test cases.

For each test case, the first line contains the only integer **n** indicating the length of the wall. (1 <= **n** <= 8)

Two lines follow, denoting the expected pattern of the wall. The color is represented by a single capital letter.

See the sample input for further details.

## 输出格式

For each test case, output only one integer denoting the minimum number of steps.

## 样例 #1

### 输入

```
3
3
ABA
CBC
3
BAA
CCB
3
BBB
BAB
```

### 输出

```
Case #1: 3
Case #2: 3
Case #3: 2
```

