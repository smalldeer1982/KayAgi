---
title: "骰子涂色 Cube painting"
layout: "post"
diff: 普及-
pid: UVA253
tag: []
---

# 骰子涂色 Cube painting

## 题目描述

输入两个骰子，判断二者是否等价。每个骰子用6个字母表示。如第一幅图所示。

例如rbgggr和rggbgr分别表示下面两幅图的两个骰子。两者是等价的，因为图1中所示的骰子沿着竖直轴旋转90°之后就可以得到图2所示的骰子。

## 输入格式

12个字母，前6个字母是第一个骰子的六个面；后6个字母是第二个骰子的六个面。

## 输出格式

一个布尔值。若两个骰子是等价的，则输出TRUE；反之输出FALSE。

## 样例 #1

### 输入

```
rbgggrrggbgr
rrrbbbrrbbbr
rbgrbgrrrrrg
```

### 输出

```
TRUE
FALSE
FALSE
```

