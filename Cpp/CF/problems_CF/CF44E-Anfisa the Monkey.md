---
title: "Anfisa the Monkey"
layout: "post"
diff: 普及-
pid: CF44E
tag: []
---

# Anfisa the Monkey

## 题目描述

Anfisa the monkey learns to type. She is yet unfamiliar with the "space" key and can only type in lower-case Latin letters. Having typed for a fairly long line, Anfisa understood that it would be great to divide what she has written into $ k $ lines not shorter than $ a $ and not longer than $ b $ , for the text to resemble human speech more. Help Anfisa.

## 输入格式

The first line contains three integers $ k $ , $ a $ and $ b $ ( $ 1<=k<=200 $ , $ 1<=a<=b<=200 $ ). The second line contains a sequence of lowercase Latin letters — the text typed by Anfisa. It is guaranteed that the given line is not empty and its length does not exceed $ 200 $ symbols.

## 输出格式

Print $ k $ lines, each of which contains no less than $ a $ and no more than $ b $ symbols — Anfisa's text divided into lines. It is not allowed to perform any changes in the text, such as: deleting or adding symbols, changing their order, etc. If the solution is not unique, print any of them. If there is no solution, print "No solution" (without quotes).

## 样例 #1

### 输入

```
3 2 5
abrakadabra

```

### 输出

```
ab
rakad
abra

```

## 样例 #2

### 输入

```
4 1 2
abrakadabra

```

### 输出

```
No solution

```

