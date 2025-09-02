---
title: "IQ Test"
layout: "post"
diff: 普及-
pid: CF287A
tag: []
---

# IQ Test

## 题目描述

In the city of Ultima Thule job applicants are often offered an IQ test.

The test is as follows: the person gets a piece of squared paper with a $ 4×4 $ square painted on it. Some of the square's cells are painted black and others are painted white. Your task is to repaint at most one cell the other color so that the picture has a $ 2×2 $ square, completely consisting of cells of the same color. If the initial picture already has such a square, the person should just say so and the test will be completed.

Your task is to write a program that determines whether it is possible to pass the test. You cannot pass the test if either repainting any cell or no action doesn't result in a $ 2×2 $ square, consisting of cells of the same color.

## 输入格式

Four lines contain four characters each: the $ j $ -th character of the $ i $ -th line equals "." if the cell in the $ i $ -th row and the $ j $ -th column of the square is painted white, and "\#", if the cell is black.

## 输出格式

Print "YES" (without the quotes), if the test can be passed and "NO" (without the quotes) otherwise.

## 说明/提示

In the first test sample it is enough to repaint the first cell in the second row. After such repainting the required $ 2×2 $ square is on the intersection of the $ 1 $ -st and $ 2 $ -nd row with the $ 1 $ -st and $ 2 $ -nd column.

## 样例 #1

### 输入

```
####
.#..
####
....

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
####
....
####
....

```

### 输出

```
NO

```

