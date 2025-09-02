---
title: "Start Up"
layout: "post"
diff: 普及/提高-
pid: CF420A
tag: []
---

# Start Up

## 题目描述

Recently, a start up by two students of a state university of city F gained incredible popularity. Now it's time to start a new company. But what do we call it?

The market analysts came up with a very smart plan: the name of the company should be identical to its reflection in a mirror! In other words, if we write out the name of the company on a piece of paper in a line (horizontally, from left to right) with large English letters, then put this piece of paper in front of the mirror, then the reflection of the name in the mirror should perfectly match the line written on the piece of paper.

There are many suggestions for the company name, so coming up to the mirror with a piece of paper for each name wouldn't be sensible. The founders of the company decided to automatize this process. They asked you to write a program that can, given a word, determine whether the word is a 'mirror' word or not.

## 输入格式

The first line contains a non-empty name that needs to be checked. The name contains at most $ 10^{5} $ large English letters. The name will be written with the next sans serif font:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF420A/accf07de9beb8006c8cbefb59ee21f43a0cca810.png)

## 输出格式

Print 'YES' (without the quotes), if the given name matches its mirror reflection. Otherwise, print 'NO' (without the quotes).

## 样例 #1

### 输入

```
AHA

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
Z

```

### 输出

```
NO

```

## 样例 #3

### 输入

```
XO

```

### 输出

```
NO

```

