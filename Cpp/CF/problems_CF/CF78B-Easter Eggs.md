---
title: "Easter Eggs"
layout: "post"
diff: 普及-
pid: CF78B
tag: []
---

# Easter Eggs

## 题目描述

The Easter Rabbit laid $ n $ eggs in a circle and is about to paint them.

Each egg should be painted one color out of 7: red, orange, yellow, green, blue, indigo or violet. Also, the following conditions should be satisfied:

- Each of the seven colors should be used to paint at least one egg.
- Any four eggs lying sequentially should be painted different colors.

Help the Easter Rabbit paint the eggs in the required manner. We know that it is always possible.

## 输入格式

The only line contains an integer $ n $ — the amount of eggs ( $ 7<=n<=100 $ ).

## 输出格式

Print one line consisting of $ n $ characters. The $ i $ -th character should describe the color of the $ i $ -th egg in the order they lie in the circle. The colors should be represented as follows: "R" stands for red, "O" stands for orange, "Y" stands for yellow, "G" stands for green, "B" stands for blue, "I" stands for indigo, "V" stands for violet.

If there are several answers, print any of them.

## 说明/提示

The way the eggs will be painted in the first sample is shown on the picture:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF78B/89e74426378989547383b9ed8ec253c74d4ce7d9.png)

## 样例 #1

### 输入

```
8

```

### 输出

```
ROYGRBIV

```

## 样例 #2

### 输入

```
13

```

### 输出

```
ROYGBIVGBIVYG

```

