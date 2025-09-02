---
title: "Secret Combination"
layout: "post"
diff: 普及/提高-
pid: CF496B
tag: []
---

# Secret Combination

## 题目描述

You got a box with a combination lock. The lock has a display showing $ n $ digits. There are two buttons on the box, each button changes digits on the display. You have quickly discovered that the first button adds 1 to all the digits (all digits 9 become digits 0), and the second button shifts all the digits on the display one position to the right (the last digit becomes the first one). For example, if the display is currently showing number 579, then if we push the first button, the display will show 680, and if after that we push the second button, the display will show 068.

You know that the lock will open if the display is showing the smallest possible number that can be obtained by pushing the buttons in some order. The leading zeros are ignored while comparing numbers. Now your task is to find the desired number.

## 输入格式

The first line contains a single integer $ n $ ( $ 1<=n<=1000 $ ) — the number of digits on the display.

The second line contains $ n $ digits — the initial state of the display.

## 输出格式

Print a single line containing $ n $ digits — the desired state of the display containing the smallest possible number.

## 样例 #1

### 输入

```
3
579

```

### 输出

```
024

```

## 样例 #2

### 输入

```
4
2014

```

### 输出

```
0142

```

