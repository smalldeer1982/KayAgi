---
title: "Colorful Stones (Simplified Edition)"
layout: "post"
diff: 入门
pid: CF265A
tag: ['模拟', '字符串']
---

# Colorful Stones (Simplified Edition)

## 题目描述

There is a sequence of colorful stones. The color of each stone is one of red, green, or blue. You are given a string $ s $ . The $ i $ -th (1-based) character of $ s $ represents the color of the $ i $ -th stone. If the character is "R", "G", or "B", the color of the corresponding stone is red, green, or blue, respectively.

Initially Squirrel Liss is standing on the first stone. You perform instructions one or more times.

Each instruction is one of the three types: "RED", "GREEN", or "BLUE". After an instruction $ c $ , if Liss is standing on a stone whose colors is $ c $ , Liss will move one stone forward, else she will not move.

You are given a string $ t $ . The number of instructions is equal to the length of $ t $ , and the $ i $ -th character of $ t $ represents the $ i $ -th instruction.

Calculate the final position of Liss (the number of the stone she is going to stand on in the end) after performing all the instructions, and print its 1-based position. It is guaranteed that Liss don't move out of the sequence.

## 输入格式

The input contains two lines. The first line contains the string $ s $ ( $ 1<=|s|<=50 $ ). The second line contains the string $ t $ ( $ 1<=|t|<=50 $ ). The characters of each string will be one of "R", "G", or "B". It is guaranteed that Liss don't move out of the sequence.

## 输出格式

Print the final 1-based position of Liss in a single line.

## 样例 #1

### 输入

```
RGB
RRR

```

### 输出

```
2

```

## 样例 #2

### 输入

```
RRRBGBRBBB
BBBRR

```

### 输出

```
3

```

## 样例 #3

### 输入

```
BRRBGBRGRBGRGRRGGBGBGBRGBRGRGGGRBRRRBRBBBGRRRGGBBB
BBRBGGRGRGBBBRBGRBRBBBBRBRRRBGBBGBBRRBBGGRBRRBRGRB

```

### 输出

```
15

```

