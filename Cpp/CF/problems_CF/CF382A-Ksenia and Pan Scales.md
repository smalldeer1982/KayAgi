---
title: "Ksenia and Pan Scales"
layout: "post"
diff: 普及-
pid: CF382A
tag: []
---

# Ksenia and Pan Scales

## 题目描述

Ksenia has ordinary pan scales and several weights of an equal mass. Ksenia has already put some weights on the scales, while other weights are untouched. Ksenia is now wondering whether it is possible to put all the remaining weights on the scales so that the scales were in equilibrium.

The scales is in equilibrium if the total sum of weights on the left pan is equal to the total sum of weights on the right pan.

## 输入格式

The first line has a non-empty sequence of characters describing the scales. In this sequence, an uppercase English letter indicates a weight, and the symbol "|" indicates the delimiter (the character occurs in the sequence exactly once). All weights that are recorded in the sequence before the delimiter are initially on the left pan of the scale. All weights that are recorded in the sequence after the delimiter are initially on the right pan of the scale.

The second line contains a non-empty sequence containing uppercase English letters. Each letter indicates a weight which is not used yet.

It is guaranteed that all the English letters in the input data are different. It is guaranteed that the input does not contain any extra characters.

## 输出格式

If you cannot put all the weights on the scales so that the scales were in equilibrium, print string "Impossible". Otherwise, print the description of the resulting scales, copy the format of the input.

If there are multiple answers, print any of them.

## 样例 #1

### 输入

```
AC|T
L

```

### 输出

```
AC|TL

```

## 样例 #2

### 输入

```
|ABC
XYZ

```

### 输出

```
XYZ|ABC

```

## 样例 #3

### 输入

```
W|T
F

```

### 输出

```
Impossible

```

## 样例 #4

### 输入

```
ABC|
D

```

### 输出

```
Impossible

```

