---
title: "Move and Turn"
layout: "post"
diff: 普及/提高-
pid: CF1459B
tag: []
---

# Move and Turn

## 题目描述

A robot is standing at the origin of the infinite two-dimensional plane. Each second the robot moves exactly $ 1 $ meter in one of the four cardinal directions: north, south, west, and east. For the first step the robot can choose any of the four directions, but then at the end of every second it has to turn 90 degrees left or right with respect to the direction it just moved in. For example, if the robot has just moved north or south, the next step it takes has to be either west or east, and vice versa.

The robot makes exactly $ n $ steps from its starting position according to the rules above. How many different points can the robot arrive to at the end? The final orientation of the robot can be ignored.

## 输入格式

The only line contains a single integer $ n $ ( $ 1 \leq n \leq 1000 $ ) — the number of steps the robot makes.

## 输出格式

Print a single integer — the number of different possible locations after exactly $ n $ steps.

## 说明/提示

In the first sample case, the robot will end up 1 meter north, south, west, or east depending on its initial direction.

In the second sample case, the robot will always end up $ \sqrt{2} $ meters north-west, north-east, south-west, or south-east.

## 样例 #1

### 输入

```
1
```

### 输出

```
4
```

## 样例 #2

### 输入

```
2
```

### 输出

```
4
```

## 样例 #3

### 输入

```
3
```

### 输出

```
12
```

