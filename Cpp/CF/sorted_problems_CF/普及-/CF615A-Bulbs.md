---
title: "Bulbs"
layout: "post"
diff: 普及-
pid: CF615A
tag: []
---

# Bulbs

## 题目描述

Vasya wants to turn on Christmas lights consisting of $ m $ bulbs. Initially, all bulbs are turned off. There are $ n $ buttons, each of them is connected to some set of bulbs. Vasya can press any of these buttons. When the button is pressed, it turns on all the bulbs it's connected to. Can Vasya light up all the bulbs?

If Vasya presses the button such that some bulbs connected to it are already turned on, they do not change their state, i.e. remain turned on.

## 输入格式

The first line of the input contains integers $ n $ and $ m $ ( $ 1<=n,m<=100 $ ) — the number of buttons and the number of bulbs respectively.

Each of the next $ n $ lines contains $ x_{i} $ ( $ 0<=x_{i}<=m $ ) — the number of bulbs that are turned on by the $ i $ -th button, and then $ x_{i} $ numbers $ y_{ij} $ ( $ 1<=y_{ij}<=m $ ) — the numbers of these bulbs.

## 输出格式

If it's possible to turn on all $ m $ bulbs print "YES", otherwise print "NO".

## 说明/提示

In the first sample you can press each button once and turn on all the bulbs. In the 2 sample it is impossible to turn on the 3-rd lamp.

## 样例 #1

### 输入

```
3 4
2 1 4
3 1 3 1
1 2

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
3 3
1 1
1 2
1 1

```

### 输出

```
NO

```

