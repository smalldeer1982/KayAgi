---
title: "Behold my quadrangle"
layout: "post"
diff: 入门
pid: UVA11455
tag: []
---

# Behold my quadrangle

## 题目描述

给出四条边的长度。你必须确定他们是否能形成一个正方形。如果不是，确定它们是否可以形成一个矩形。如果不是，确定它们是否可以形成四边形。

## 输入格式

输入的第一行包含一个整数，指示测试用例的数量。 对于每个测试用例，有一行包含四个正整数，介于 00 和 230230 之间。

## 输出格式

对于每个测试点，如果对应输入的边可以分别形成一个正方形、一个矩形、一个四边形或不能组成，那么分别输出“square”、“rectangle”、“quadrangle”或“banana”。

## 样例 #1

### 输入

```
4
10 8 7 6
9 1 9 1
29 29 29 29
5 12 30 7
```

### 输出

```
quadrangle
rectangle
square
banana
```

