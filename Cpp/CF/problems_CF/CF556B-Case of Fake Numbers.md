---
title: "Case of Fake Numbers"
layout: "post"
diff: 普及-
pid: CF556B
tag: []
---

# Case of Fake Numbers

## 题目描述

Andrewid the Android is a galaxy-famous detective. He is now investigating a case of frauds who make fake copies of the famous Stolp's gears, puzzles that are as famous as the Rubik's cube once was.

Its most important components are a button and a line of $ n $ similar gears. Each gear has $ n $ teeth containing all numbers from $ 0 $ to $ n-1 $ in the counter-clockwise order. When you push a button, the first gear rotates clockwise, then the second gear rotates counter-clockwise, the the third gear rotates clockwise an so on.

Besides, each gear has exactly one active tooth. When a gear turns, a new active tooth is the one following after the current active tooth according to the direction of the rotation. For example, if $ n=5 $ , and the active tooth is the one containing number $ 0 $ , then clockwise rotation makes the tooth with number $ 1 $ active, or the counter-clockwise rotating makes the tooth number $ 4 $ active.

Andrewid remembers that the real puzzle has the following property: you can push the button multiple times in such a way that in the end the numbers on the active teeth of the gears from first to last form sequence $ 0,1,2,...,n-1 $ . Write a program that determines whether the given puzzle is real or fake.

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=1000 $ ) — the number of gears.

The second line contains $ n $ digits $ a_{1},a_{2},...,a_{n} $ ( $ 0<=a_{i}<=n-1 $ ) — the sequence of active teeth: the active tooth of the $ i $ -th gear contains number $ a_{i} $ .

## 输出格式

In a single line print "Yes" (without the quotes), if the given Stolp's gears puzzle is real, and "No" (without the quotes) otherwise.

## 说明/提示

In the first sample test when you push the button for the first time, the sequence of active teeth will be 2 2 1, when you push it for the second time, you get 0 1 2.

## 样例 #1

### 输入

```
3
1 0 0

```

### 输出

```
Yes

```

## 样例 #2

### 输入

```
5
4 2 1 4 3

```

### 输出

```
Yes

```

## 样例 #3

### 输入

```
4
0 2 3 1

```

### 输出

```
No

```

