---
title: "Crossword"
layout: "post"
diff: 普及+/提高
pid: CF47C
tag: ['模拟']
---

# Crossword

## 题目描述

Vasya trains to compose crossword puzzles. He can only compose crosswords of a very simplе type so far. All of them consist of exactly six words; the words can be read only from top to bottom vertically and from the left to the right horizontally. The words are arranged in the form of a rectangular "eight" or infinity sign, not necessarily symmetrical.

The top-left corner of the crossword coincides with the top-left corner of the rectangle. The same thing is correct for the right-bottom corners. The crossword can't degrade, i.e. it always has exactly four blank areas, two of which are surrounded by letters. Look into the output for the samples for clarification.

Help Vasya — compose a crossword of the described type using the given six words. It is allowed to use the words in any order.

## 输入格式

Six lines contain the given words. Every word consists of no more than 30 and no less than 3 uppercase Latin letters.

## 输出格式

If it is impossible to solve the problem, print Impossible. Otherwise, print the sought crossword. All the empty squares should be marked as dots.

If there can be several solutions to that problem, print the lexicographically minimum one. I.e. the solution where the first line is less than the first line of other solutions should be printed. If the two lines are equal, compare the second lines and so on. The lexicographical comparison of lines is realized by the < operator in the modern programming languages.

## 样例 #1

### 输入

```
NOD
BAA
YARD
AIRWAY
NEWTON
BURN

```

### 输出

```
BAA...
U.I...
R.R...
NEWTON
..A..O
..YARD

```

## 样例 #2

### 输入

```
AAA
AAA
AAAAA
AAA
AAA
AAAAA

```

### 输出

```
AAA..
A.A..
AAAAA
..A.A
..AAA

```

## 样例 #3

### 输入

```
PTC
JYNYFDSGI
ZGPPC
IXEJNDOP
JJFS
SSXXQOFGJUZ

```

### 输出

```
JJFS....
Y..S....
N..X....
Y..X....
F..Q....
D..O....
S..F....
G..G....
IXEJNDOP
...U...T
...ZGPPC

```

