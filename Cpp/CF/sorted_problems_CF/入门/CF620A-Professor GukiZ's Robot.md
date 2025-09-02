---
title: "Professor GukiZ's Robot"
layout: "post"
diff: 入门
pid: CF620A
tag: []
---

# Professor GukiZ's Robot

## 题目描述

Professor GukiZ makes a new robot. The robot are in the point with coordinates $ (x_{1},y_{1}) $ and should go to the point $ (x_{2},y_{2}) $ . In a single step the robot can change any of its coordinates (maybe both of them) by one (decrease or increase). So the robot can move in one of the $ 8 $ directions. Find the minimal number of steps the robot should make to get the finish position.

## 输入格式

The first line contains two integers $ x_{1},y_{1} $ ( $ -10^{9}<=x_{1},y_{1}<=10^{9} $ ) — the start position of the robot.

The second line contains two integers $ x_{2},y_{2} $ ( $ -10^{9}<=x_{2},y_{2}<=10^{9} $ ) — the finish position of the robot.

## 输出格式

Print the only integer $ d $ — the minimal number of steps to get the finish position.

## 说明/提示

In the first example robot should increase both of its coordinates by one four times, so it will be in position $ (4,4) $ . After that robot should simply increase its $ y $ coordinate and get the finish position.

In the second example robot should simultaneously increase $ x $ coordinate and decrease $ y $ coordinate by one three times.

## 样例 #1

### 输入

```
0 0
4 5

```

### 输出

```
5

```

## 样例 #2

### 输入

```
3 4
6 1

```

### 输出

```
3

```

