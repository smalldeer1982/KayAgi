---
title: "Raising Bacteria"
layout: "post"
diff: 入门
pid: CF579A
tag: []
---

# Raising Bacteria

## 题目描述

You are a lover of bacteria. You want to raise some bacteria in a box.

Initially, the box is empty. Each morning, you can put any number of bacteria into the box. And each night, every bacterium in the box will split into two bacteria. You hope to see exactly $ x $ bacteria in the box at some moment.

What is the minimum number of bacteria you need to put into the box across those days?

## 输入格式

The only line containing one integer $ x $ ( $ 1<=x<=10^{9} $ ).

## 输出格式

The only line containing one integer: the answer.

## 说明/提示

For the first sample, we can add one bacterium in the box in the first day morning and at the third morning there will be $ 4 $ bacteria in the box. Now we put one more resulting $ 5 $ in the box. We added $ 2 $ bacteria in the process so the answer is $ 2 $ .

For the second sample, we can put one in the first morning and in the 4-th morning there will be $ 8 $ in the box. So the answer is $ 1 $ .

## 样例 #1

### 输入

```
5

```

### 输出

```
2

```

## 样例 #2

### 输入

```
8

```

### 输出

```
1

```

