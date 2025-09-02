---
title: "Two Buttons"
layout: "post"
diff: 普及/提高-
pid: CF520B
tag: []
---

# Two Buttons

## 题目描述

Vasya has found a strange device. On the front panel of a device there are: a red button, a blue button and a display showing some positive integer. After clicking the red button, device multiplies the displayed number by two. After clicking the blue button, device subtracts one from the number on the display. If at some point the number stops being positive, the device breaks down. The display can show arbitrarily large numbers. Initially, the display shows number $ n $ .

Bob wants to get number $ m $ on the display. What minimum number of clicks he has to make in order to achieve this result?

## 输入格式

The first and the only line of the input contains two distinct integers $ n $ and $ m $ ( $ 1<=n,m<=10^{4} $ ), separated by a space .

## 输出格式

Print a single number — the minimum number of times one needs to push the button required to get the number $ m $ out of number $ n $ .

## 说明/提示

In the first example you need to push the blue button once, and then push the red button once.

In the second example, doubling the number is unnecessary, so we need to push the blue button nine times.

## 样例 #1

### 输入

```
4 6

```

### 输出

```
2

```

## 样例 #2

### 输入

```
10 1

```

### 输出

```
9

```

